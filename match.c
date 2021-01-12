
#include <time.h>
#include <setjmp.h>
#include <ctype.h>

#include "lapi.h"
#include "lauxlib.h"
#include "lcode.h"
#include "lctype.h"
#include "ldebug.h"
#include "ldo.h"
#include "lfunc.h"
#include "lgc.h"
#include "llex.h"
#include "llimits.h"
#include "lmem.h"
#include "lobject.h"
#include "lopcodes.h"
#include "lopnames.h"
#include "lparser.h"
#include "lprefix.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "ltm.h"
#include "luaconf.h"
#include "lua.h"
#include "lualib.h"
#include "lundump.h"
#include "lvm.h"
#include "lzio.h"

typedef struct MatchState {
  const char *src_init;
  const char *src_end;
  const char *p_end;
  lua_State *L;
  int matchdepth;
  unsigned char level;
  struct {
    const char *init;
    ptrdiff_t len;
  } capture[32];
} MatchState;


extern const char * max_expand(MatchState *, const char *, const char *, const char *);
static const char * min_expand (MatchState *, const char *, const char *, const char *);
extern int singlematch(MatchState *, const char *, const char *, const char *);
extern const char * classend(MatchState *, const char *);
extern const char * match_capture(MatchState *, const char *, int);
extern int matchbracketclass(int, const char *, const char *);
extern int luaL_error(lua_State *, const char *, ...);
extern const char * matchbalance(MatchState *, const char *, const char *);
extern const char * end_capture(MatchState *, const char *, const char *);
extern const char * start_capture(MatchState *, const char *, const char *, int);
extern int luaL_error(lua_State *, const char *, ...);

static const char *match (MatchState *ms, const char *s, const char *p) {
  if (ms->matchdepth-- == 0)
    luaL_error(ms->L, "pattern too complex");
  init:
  if (p != ms->p_end) {
    switch (*p) {
      case '(': {
        if (*(p + 1) == ')')
          s = start_capture(ms, s, p + 2, (-2));
        else
          s = start_capture(ms, s, p + 1, (-1));
        break;
      }
      case ')': {
        s = end_capture(ms, s, p + 1);
        break;
      }
      case '$': {
        if ((p + 1) != ms->p_end)
          goto dflt;
        s = (s == ms->src_end) ? s : ((void*)0);
        break;
      }
      case '%': {
        switch (*(p + 1)) {
          case 'b': {
            s = matchbalance(ms, s, p + 2);
            if (s != ((void*)0)) {
              p += 4; goto init;
            }
            break;
          }
          case 'f': {
            const char *ep; char previous;
            p += 2;
            if (*p != '[')
              luaL_error(ms->L, "missing '[' after '%%f' in pattern");
            ep = classend(ms, p);
            previous = (s == ms->src_init) ? '\0' : *(s - 1);
            if (!matchbracketclass(((unsigned char)(previous)), p, ep - 1) &&
               matchbracketclass(((unsigned char)(*s)), p, ep - 1)) {
              p = ep; goto init;
            }
            s = ((void*)0);
            break;
          }
          case '0': case '1': case '2': case '3':
          case '4': case '5': case '6': case '7':
          case '8': case '9': {
            s = match_capture(ms, s, ((unsigned char)(*(p + 1))));
            if (s != ((void*)0)) {
              p += 2; goto init;
            }
            break;
          }
          default: goto dflt;
        }
        break;
      }
      default: dflt: {
        const char *ep = classend(ms, p);

        if (!singlematch(ms, s, p, ep)) {
          if (*ep == '*' || *ep == '?' || *ep == '-') {
            p = ep + 1; goto init;
          }
          else
            s = ((void*)0);
        }
        else {
          switch (*ep) {
            case '?': {
              const char *res;
              if ((res = match(ms, s + 1, ep + 1)) != ((void*)0))
                s = res;
              else {
                p = ep + 1; goto init;
              }
              break;
            }
            case '+':
              s++;

            case '*':
              s = max_expand(ms, s, p, ep);
              break;
            case '-':
              s = min_expand(ms, s, p, ep);
              break;
            default:
              s++; p = ep; goto init;
          }
        }
        break;
      }
    }
  }
  ms->matchdepth++;
  return s;
}
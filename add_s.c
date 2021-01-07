
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


extern void luaL_addlstring(luaL_Buffer *, const char *, size_t);
extern int luaL_error(lua_State *, const char *, ...);
extern void luaL_addlstring(luaL_Buffer *, const char *, size_t);
extern void luaL_addvalue(luaL_Buffer *);
extern size_t get_onecapture(MatchState *, int, const char *, const char *, const char **);
extern const unsigned short ** __ctype_b_loc();
extern void luaL_addlstring(luaL_Buffer *, const char *, size_t);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern void luaL_addlstring(luaL_Buffer *, const char *, size_t);
extern void * memchr(const void *, int, size_t);
extern const char * lua_tolstring(lua_State *, int, size_t *);

static void add_s (MatchState *ms, luaL_Buffer *b, const char *s,
                                                   const char *e) {
  size_t l;
  lua_State *L = ms->L;
  const char *news = lua_tolstring(L, 3, &l);
  const char *p;
  while ((p = (char *)memchr(news, '%', l)) != ((void*)0)) {
    luaL_addlstring(b, news, p - news);
    p++;
    if (*p == '%')
      ((void)((b)->n < (b)->size || luaL_prepbuffsize((b), 1)), ((b)->b[(b)->n++] = (*p)));
    else if (*p == '0')
        luaL_addlstring(b, s, e - s);
    else if (((*__ctype_b_loc ())[(int) ((((unsigned char)(*p))))] & (unsigned short int) _ISdigit)) {
      const char *cap;
      ptrdiff_t resl = get_onecapture(ms, *p - '1', s, e, &cap);
      if (resl == (-2))
        luaL_addvalue(b);
      else
        luaL_addlstring(b, cap, resl);
    }
    else
      luaL_error(L, "invalid use of '%c' in replacement string", '%');
    l -= p + 1 - news;
    news = p + 1;
  }
  luaL_addlstring(b, news, l);
}
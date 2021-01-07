
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


extern const char * match(MatchState *, const char *, const char *);
extern int singlematch(MatchState *, const char *, const char *, const char *);

static const char *max_expand (MatchState *ms, const char *s,
                                 const char *p, const char *ep) {
  ptrdiff_t i = 0;
  while (singlematch(ms, s + i, p, ep))
    i++;

  while (i>=0) {
    const char *res = match(ms, (s+i), ep+1);
    if (res) return res;
    i--;
  }
  return ((void*)0);
}
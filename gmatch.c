
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

typedef struct GMatchState {
  const char *src;
  const char *p;
  const char *lastmatch;
  MatchState ms;
} GMatchState;
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


extern void lua_pushcclosure(lua_State *, lua_CFunction, int);
extern void prepstate(MatchState *, lua_State *, const char *, size_t, const char *, size_t);
extern void * lua_newuserdatauv(lua_State *, size_t, int);
extern void lua_settop(lua_State *, int);
extern size_t posrelatI(lua_Integer, size_t);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

static int gmatch (lua_State *L) {
  size_t ls, lp;
  const char *s = luaL_checklstring(L, 1, &ls);
  const char *p = luaL_checklstring(L, 2, &lp);
  size_t init = posrelatI(luaL_optinteger(L, 3, 1), ls) - 1;
  GMatchState *gm;
  lua_settop(L, 2);
  gm = (GMatchState *)lua_newuserdatauv(L, sizeof(GMatchState), 0);
  if (init > ls)
    init = ls + 1;
  prepstate(&gm->ms, L, s, ls, p, lp);
  gm->src = s + init; gm->p = p; gm->lastmatch = ((void*)0);
  lua_pushcclosure(L, gmatch_aux, 3);
  return 1;
}
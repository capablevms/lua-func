
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

static const char *const HOOKKEY = "_HOOKKEY";

extern void lua_sethook(lua_State *, lua_Hook, int, int);
extern void lua_rawset(lua_State *, int);
extern void lua_pushvalue(lua_State *, int);
extern void lua_xmove(lua_State *, lua_State *, int);
extern int lua_pushthread(lua_State *);
extern void checkstack(lua_State *, lua_State *, int);
extern int lua_setmetatable(lua_State *, int);
extern void lua_pushvalue(lua_State *, int);
extern void lua_setfield(lua_State *, int, const char *);
extern const char * lua_pushstring(lua_State *, const char *);
extern int luaL_getsubtable(lua_State *, int, const char *);
extern int makemask(const char *, int);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern void luaL_checktype(lua_State *, int, int);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern void lua_settop(lua_State *, int);
extern int lua_type(lua_State *, int);
extern lua_State * getthread(lua_State *, int *);

extern void hookf (lua_State *L, lua_Debug *ar);

extern int db_sethook (lua_State *L) {
  int arg, mask, count;
  lua_Hook func;
  lua_State *L1 = getthread(L, &arg);
  if ((lua_type(L, (arg+1)) <= 0)) {
    lua_settop(L, arg+1);
    func = ((void*)0); mask = 0; count = 0;
  }
  else {
    const char *smask = (luaL_checklstring(L, (arg+2), ((void*)0)));
    luaL_checktype(L, arg+1, 6);
    count = (int)luaL_optinteger(L, arg + 3, 0);
    func = hookf; mask = makemask(smask, count);
  }
  if (!luaL_getsubtable(L, (-1000000 - 1000), HOOKKEY)) {

    lua_pushstring(L, "k");
    lua_setfield(L, -2, "__mode");
    lua_pushvalue(L, -1);
    lua_setmetatable(L, -2);
  }
  checkstack(L, L1, 1);
  lua_pushthread(L1); lua_xmove(L1, L, 1);
  lua_pushvalue(L, arg + 1);
  lua_rawset(L, -3);
  lua_sethook(L1, func, mask, count);
  return 0;
}
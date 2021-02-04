
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

extern int arith_unm(lua_State *);
extern int arith_idiv(lua_State *);
extern int arith_div(lua_State *);
extern int arith_pow(lua_State *);
extern int arith_mod(lua_State *);
extern int arith_mul(lua_State *);
extern int arith_sub(lua_State *);
extern int arith_add(lua_State *);

static const luaL_Reg stringmetamethods[] = {
  {"__add", arith_add},
  {"__sub", arith_sub},
  {"__mul", arith_mul},
  {"__mod", arith_mod},
  {"__pow", arith_pow},
  {"__div", arith_div},
  {"__idiv", arith_idiv},
  {"__unm", arith_unm},
  {"__index", ((void*)0)},
  {((void*)0), ((void*)0)}
};

extern void lua_settop(lua_State *, int);
extern void lua_setfield(lua_State *, int, const char *);
extern void lua_pushvalue(lua_State *, int);
extern void lua_settop(lua_State *, int);
extern int lua_setmetatable(lua_State *, int);
extern void lua_pushvalue(lua_State *, int);
extern const char * lua_pushstring(lua_State *, const char *);
extern void luaL_setfuncs(lua_State *, const luaL_Reg *, int);
extern void lua_createtable(lua_State *, int, int);

extern void createmetatable (lua_State *L) {

  lua_createtable(L, 0, sizeof(stringmetamethods)/sizeof((stringmetamethods)[0]) - 1);
  luaL_setfuncs(L, stringmetamethods, 0);
  lua_pushstring(L, "" "");
  lua_pushvalue(L, -2);
  lua_setmetatable(L, -2);
  lua_settop(L, -(1)-1);
  lua_pushvalue(L, -2);
  lua_setfield(L, -2, "__index");
  lua_settop(L, -(1)-1);
}
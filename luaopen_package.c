
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

extern int ll_searchpath(lua_State *);
extern int ll_loadlib(lua_State *);
extern const luaL_Reg ll_funcs;

static const luaL_Reg pk_funcs[] = {
  {"loadlib", ll_loadlib},
  {"searchpath", ll_searchpath},

  {"preload", ((void*)0)},
  {"cpath", ((void*)0)},
  {"path", ((void*)0)},
  {"searchers", ((void*)0)},
  {"loaded", ((void*)0)},
  {((void*)0), ((void*)0)}
};

extern void lua_settop(lua_State *, int);
extern void luaL_setfuncs(lua_State *, const luaL_Reg *, int);
extern void lua_pushvalue(lua_State *, int);
extern int lua_rawgeti(lua_State *, int, lua_Integer);
extern void lua_setfield(lua_State *, int, const char *);
extern int luaL_getsubtable(lua_State *, int, const char *);
extern void lua_setfield(lua_State *, int, const char *);
extern int luaL_getsubtable(lua_State *, int, const char *);
extern void lua_setfield(lua_State *, int, const char *);
extern const char * lua_pushstring(lua_State *, const char *);
extern void setpath(lua_State *, const char *, const char *, const char *);
extern void setpath(lua_State *, const char *, const char *, const char *);
extern void createsearcherstable(lua_State *);
extern void luaL_setfuncs(lua_State *, const luaL_Reg *, int);
extern void lua_createtable(lua_State *, int, int);
extern void luaL_checkversion_(lua_State *, lua_Number, size_t);
extern void createclibstable(lua_State *);

extern int luaopen_package (lua_State *L) {
  createclibstable(L);
  (luaL_checkversion_(L, 504, (sizeof(lua_Integer)*16 + sizeof(lua_Number))), lua_createtable(L, 0, sizeof(pk_funcs)/sizeof((pk_funcs)[0]) - 1), luaL_setfuncs(L,pk_funcs,0));
  createsearcherstable(L);

  setpath(L, "path", "LUA_PATH", "/usr/local/" "share/lua/" "5" "." "4" "/""?.lua;" "/usr/local/" "share/lua/" "5" "." "4" "/""?/init.lua;" "/usr/local/" "lib/lua/" "5" "." "4" "/""?.lua;" "/usr/local/" "lib/lua/" "5" "." "4" "/""?/init.lua;" "./?.lua;" "./?/init.lua");
  setpath(L, "cpath", "LUA_CPATH", "/usr/local/" "lib/lua/" "5" "." "4" "/""?.so;" "/usr/local/" "lib/lua/" "5" "." "4" "/""loadall.so;" "./?.so");

  lua_pushstring(L, "" "/" "\n" ";" "\n" "?" "\n" "!" "\n" "-" "\n");

  lua_setfield(L, -2, "config");

  luaL_getsubtable(L, (-1000000 - 1000), "_LOADED");
  lua_setfield(L, -2, "loaded");

  luaL_getsubtable(L, (-1000000 - 1000), "_PRELOAD");
  lua_setfield(L, -2, "preload");
  ((void)lua_rawgeti(L, (-1000000 - 1000), 2));
  lua_pushvalue(L, -2);
  luaL_setfuncs(L, &ll_funcs, 1);
  lua_settop(L, -(1)-1);
  return 1;
}
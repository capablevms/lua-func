
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



extern void lua_setglobal(lua_State *, const char *);
extern void lua_pushvalue(lua_State *, int);
extern void lua_settop(lua_State *, int);
extern void lua_rotate(lua_State *, int, int);
extern void lua_setfield(lua_State *, int, const char *);
extern void lua_pushvalue(lua_State *, int);
extern void lua_callk(lua_State *, int, int, lua_KContext, lua_KFunction);
extern const char * lua_pushstring(lua_State *, const char *);
extern void lua_pushcclosure(lua_State *, lua_CFunction, int);
extern void lua_settop(lua_State *, int);
extern int lua_toboolean(lua_State *, int);
extern int lua_getfield(lua_State *, int, const char *);
extern int luaL_getsubtable(lua_State *, int, const char *);

extern void luaL_requiref (lua_State *L, const char *modname,
                               lua_CFunction openf, int glb) {
  luaL_getsubtable(L, (-1000000 - 1000), "_LOADED");
  lua_getfield(L, -1, modname);
  if (!lua_toboolean(L, -1)) {
    lua_settop(L, -(1)-1);
    lua_pushcclosure(L, (openf), 0);
    lua_pushstring(L, modname);
    lua_callk(L, (1), (1), 0, ((void*)0));
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, modname);
  }
  (lua_rotate(L, (-2), -1), lua_settop(L, -(1)-1));
  if (glb) {
    lua_pushvalue(L, -1);
    lua_setglobal(L, modname);
  }
}
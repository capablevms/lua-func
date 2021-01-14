
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



extern const char * lua_pushstring(lua_State *, const char *);
extern void lua_settop(lua_State *, int);
extern const char * lua_setlocal(lua_State *, const lua_Debug *, int);
extern void lua_xmove(lua_State *, lua_State *, int);
extern void checkstack(lua_State *, lua_State *, int);
extern void lua_settop(lua_State *, int);
extern void luaL_checkany(lua_State *, int);
extern int luaL_argerror(lua_State *, int, const char *);
extern int lua_getstack(lua_State *, int, lua_Debug *);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern lua_State * getthread(lua_State *, int *);

extern int db_setlocal (lua_State *L) {
  int arg;
  const char *name;
  lua_State *L1 = getthread(L, &arg);
  lua_Debug ar;
  int level = (int)luaL_checkinteger(L, arg + 1);
  int nvar = (int)luaL_checkinteger(L, arg + 2);
  if (!lua_getstack(L1, level, &ar))
    return luaL_argerror(L, arg+1, "level out of range");
  luaL_checkany(L, arg+3);
  lua_settop(L, arg+3);
  checkstack(L, L1, 1);
  lua_xmove(L, L1, 1);
  name = lua_setlocal(L1, &ar, nvar);
  if (name == ((void*)0))
    lua_settop(L1, -(1)-1);
  lua_pushstring(L, name);
  return 1;
}
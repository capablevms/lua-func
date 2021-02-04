
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



extern void lua_pushnil(lua_State *);
extern void lua_rotate(lua_State *, int, int);
extern const char * lua_pushstring(lua_State *, const char *);
extern void lua_xmove(lua_State *, lua_State *, int);
extern const char * lua_getlocal(lua_State *, const lua_Debug *, int);
extern void checkstack(lua_State *, lua_State *, int);
extern int luaL_argerror(lua_State *, int, const char *);
extern int lua_getstack(lua_State *, int, lua_Debug *);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern const char * lua_pushstring(lua_State *, const char *);
extern const char * lua_getlocal(lua_State *, const lua_Debug *, int);
extern void lua_pushvalue(lua_State *, int);
extern int lua_type(lua_State *, int);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern lua_State * getthread(lua_State *, int *);

extern int db_getlocal (lua_State *L) {
  int arg;
  lua_State *L1 = getthread(L, &arg);
  int nvar = (int)luaL_checkinteger(L, arg + 2);
  if ((lua_type(L, (arg + 1)) == 6)) {
    lua_pushvalue(L, arg + 1);
    lua_pushstring(L, lua_getlocal(L, ((void*)0), nvar));
    return 1;
  }
  else {
    lua_Debug ar;
    const char *name;
    int level = (int)luaL_checkinteger(L, arg + 1);
    if (!lua_getstack(L1, level, &ar))
      return luaL_argerror(L, arg+1, "level out of range");
    checkstack(L, L1, 1);
    name = lua_getlocal(L1, &ar, nvar);
    if (name) {
      lua_xmove(L1, L, 1);
      lua_pushstring(L, name);
      lua_rotate(L, -2, 1);
      return 2;
    }
    else {
      lua_pushnil(L);
      return 1;
    }
  }
}
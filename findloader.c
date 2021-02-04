
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



extern void lua_settop(lua_State *, int);
extern void luaL_addvalue(luaL_Buffer *);
extern void lua_settop(lua_State *, int);
extern int lua_isstring(lua_State *, int);
extern int lua_type(lua_State *, int);
extern void lua_callk(lua_State *, int, int, lua_KContext, lua_KFunction);
extern const char * lua_pushstring(lua_State *, const char *);
extern int luaL_error(lua_State *, const char *, ...);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern void luaL_pushresult(luaL_Buffer *);
extern void lua_settop(lua_State *, int);
extern int lua_rawgeti(lua_State *, int, lua_Integer);
extern void luaL_addstring(luaL_Buffer *, const char *);
extern void luaL_buffinit(lua_State *, luaL_Buffer *);
extern int luaL_error(lua_State *, const char *, ...);
extern int lua_getfield(lua_State *, int, const char *);

extern void findloader (lua_State *L, const char *name) {
  int i;
  luaL_Buffer msg;

  if (lua_getfield(L, ((-1000000 - 1000) - (1)), "searchers") != 5)
    luaL_error(L, "'package.searchers' must be a table");
  luaL_buffinit(L, &msg);

  for (i = 1; ; i++) {
    luaL_addstring(&msg, "\n\t");
    if (lua_rawgeti(L, 3, i) == 0) {
      lua_settop(L, -(1)-1);
      ((&msg)->n -= (2));
      luaL_pushresult(&msg);
      luaL_error(L, "module '%s' not found:%s", name, lua_tolstring(L, (-1), ((void*)0)));
    }
    lua_pushstring(L, name);
    lua_callk(L, (1), (2), 0, ((void*)0));
    if ((lua_type(L, (-2)) == 6))
      return;
    else if (lua_isstring(L, -2)) {
      lua_settop(L, -(1)-1);
      luaL_addvalue(&msg);
    }
    else {
      lua_settop(L, -(2)-1);
      ((&msg)->n -= (2));
    }
  }
}
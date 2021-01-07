
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



extern const char * lua_tolstring(lua_State *, int, size_t *);
extern void lua_settop(lua_State *, int);
extern void lua_copy(lua_State *, int, int);
extern int luaL_error(lua_State *, const char *, ...);
extern int lua_isstring(lua_State *, int);
extern void lua_settop(lua_State *, int);
extern int lua_type(lua_State *, int);
extern void lua_callk(lua_State *, int, int, lua_KContext, lua_KFunction);
extern void lua_pushvalue(lua_State *, int);
extern void luaL_checkstack(lua_State *, int, const char *);

static const char *generic_reader (lua_State *L, void *ud, size_t *size) {
  (void)(ud);
  luaL_checkstack(L, 2, "too many nested functions");
  lua_pushvalue(L, 1);
  lua_callk(L, (0), (1), 0, ((void*)0));
  if ((lua_type(L, (-1)) == 0)) {
    lua_settop(L, -(1)-1);
    *size = 0;
    return ((void*)0);
  }
  else if (!lua_isstring(L, -1))
    luaL_error(L, "reader function must return a string");
  (lua_copy(L, -1, (5)), lua_settop(L, -(1)-1));
  return lua_tolstring(L, 5, size);
}
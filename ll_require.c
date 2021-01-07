
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



extern void lua_rotate(lua_State *, int, int);
extern void lua_setfield(lua_State *, int, const char *);
extern void lua_copy(lua_State *, int, int);
extern void lua_pushboolean(lua_State *, int);
extern int lua_getfield(lua_State *, int, const char *);
extern void lua_settop(lua_State *, int);
extern void lua_setfield(lua_State *, int, const char *);
extern int lua_type(lua_State *, int);
extern void lua_callk(lua_State *, int, int, lua_KContext, lua_KFunction);
extern void lua_pushvalue(lua_State *, int);
extern void lua_pushvalue(lua_State *, int);
extern void lua_rotate(lua_State *, int, int);
extern void findloader(lua_State *, const char *);
extern void lua_settop(lua_State *, int);
extern int lua_toboolean(lua_State *, int);
extern int lua_getfield(lua_State *, int, const char *);
extern int lua_getfield(lua_State *, int, const char *);
extern void lua_settop(lua_State *, int);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

static int ll_require (lua_State *L) {
  const char *name = (luaL_checklstring(L, (1), ((void*)0)));
  lua_settop(L, 1);
  lua_getfield(L, (-1000000 - 1000), "_LOADED");
  lua_getfield(L, 2, name);
  if (lua_toboolean(L, -1))
    return 1;

  lua_settop(L, -(1)-1);
  findloader(L, name);
  lua_rotate(L, -2, 1);
  lua_pushvalue(L, 1);
  lua_pushvalue(L, -3);

  lua_callk(L, (2), (1), 0, ((void*)0));

  if (!(lua_type(L, (-1)) == 0))
    lua_setfield(L, 2, name);
  else
    lua_settop(L, -(1)-1);
  if (lua_getfield(L, 2, name) == 0) {
    lua_pushboolean(L, 1);
    lua_copy(L, -1, -2);
    lua_setfield(L, 2, name);
  }
  lua_rotate(L, -2, 1);
  return 2;
}
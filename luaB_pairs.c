
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



extern void lua_callk(lua_State *, int, int, lua_KContext, lua_KFunction);
extern void lua_pushvalue(lua_State *, int);
extern void lua_pushnil(lua_State *);
extern void lua_pushvalue(lua_State *, int);
extern void lua_pushcclosure(lua_State *, lua_CFunction, int);
extern int luaL_getmetafield(lua_State *, int, const char *);
extern void luaL_checkany(lua_State *, int);

extern int luaB_next (lua_State *);

extern int luaB_pairs (lua_State *L) {
  luaL_checkany(L, 1);
  if (luaL_getmetafield(L, 1, "__pairs") == 0) {
    lua_pushcclosure(L, (luaB_next), 0);
    lua_pushvalue(L, 1);
    lua_pushnil(L);
  }
  else {
    lua_pushvalue(L, 1);
    lua_callk(L, (1), (3), 0, ((void*)0));
  }
  return 3;
}
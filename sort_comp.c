
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
extern int lua_toboolean(lua_State *, int);
extern void lua_callk(lua_State *, int, int, lua_KContext, lua_KFunction);
extern void lua_pushvalue(lua_State *, int);
extern void lua_pushvalue(lua_State *, int);
extern void lua_pushvalue(lua_State *, int);
extern int lua_compare(lua_State *, int, int, int);
extern int lua_type(lua_State *, int);

static int sort_comp (lua_State *L, int a, int b) {
  if ((lua_type(L, (2)) == 0))
    return lua_compare(L, a, b, 1);
  else {
    int res;
    lua_pushvalue(L, 2);
    lua_pushvalue(L, a-1);
    lua_pushvalue(L, b-2);
    lua_callk(L, (2), (1), 0, ((void*)0));
    res = lua_toboolean(L, -1);
    lua_settop(L, -(1)-1);
    return res;
  }
}

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
extern void lua_rotate(lua_State *, int, int);
extern void lua_settop(lua_State *, int);
extern int lua_rawget(lua_State *, int);
extern const char * lua_pushstring(lua_State *, const char *);
extern int lua_getmetatable(lua_State *, int);

extern int luaL_getmetafield (lua_State *L, int obj, const char *event) {
  if (!lua_getmetatable(L, obj))
    return 0;
  else {
    int tt;
    lua_pushstring(L, event);
    tt = lua_rawget(L, -2);
    if (tt == 0)
      lua_settop(L, -(2)-1);
    else
      (lua_rotate(L, (-2), -1), lua_settop(L, -(1)-1));
    return tt;
  }
}
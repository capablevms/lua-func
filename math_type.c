
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
extern void luaL_checkany(lua_State *, int);
extern const char * lua_pushstring(lua_State *, const char *);
extern int lua_isinteger(lua_State *, int);
extern int lua_type(lua_State *, int);

static int math_type (lua_State *L) {
  if (lua_type(L, 1) == 3)
    lua_pushstring(L, (lua_isinteger(L, 1)) ? "integer" : "float");
  else {
    luaL_checkany(L, 1);
    lua_pushnil(L);
  }
  return 1;
}
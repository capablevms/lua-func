
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
extern const char * lua_typename(lua_State *, int);
extern int luaL_argerror(lua_State *, int, const char *);
extern int lua_type(lua_State *, int);

static int luaB_type (lua_State *L) {
  int t = lua_type(L, 1);
  ((void)((t != (-1)) || luaL_argerror(L, (1), ("value expected"))));
  lua_pushstring(L, lua_typename(L, t));
  return 1;
}
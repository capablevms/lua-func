
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



extern void lua_pushvalue(lua_State *, int);
extern int lua_compare(lua_State *, int, int, int);
extern int luaL_argerror(lua_State *, int, const char *);
extern int lua_gettop(lua_State *);

static int math_min (lua_State *L) {
  int n = lua_gettop(L);
  int imin = 1;
  int i;
  ((void)((n >= 1) || luaL_argerror(L, (1), ("value expected"))));
  for (i = 2; i <= n; i++) {
    if (lua_compare(L, i, imin, 1))
      imin = i;
  }
  lua_pushvalue(L, imin);
  return 1;
}

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



extern void lua_pushinteger(lua_State *, lua_Integer);
extern lua_Unsigned lua_rawlen(lua_State *, int);
extern int luaL_typeerror(lua_State *, int, const char *);
extern int lua_type(lua_State *, int);

extern int luaB_rawlen (lua_State *L) {
  int t = lua_type(L, 1);
  ((void)((t == 5 || t == 4) || luaL_typeerror(L, (1), ("table or string"))));

  lua_pushinteger(L, lua_rawlen(L, 1));
  return 1;
}
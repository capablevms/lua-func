
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



extern void lua_setfield(lua_State *, int, const char *);
extern const char * lua_pushstring(lua_State *, const char *);
extern void lua_setfield(lua_State *, int, const char *);
extern void lua_pushvalue(lua_State *, int);
extern void luaL_setfuncs(lua_State *, const luaL_Reg *, int);
extern int lua_rawgeti(lua_State *, int, lua_Integer);

extern int luaopen_base (lua_State *L) {

  ((void)lua_rawgeti(L, (-1000000 - 1000), 2));
  luaL_setfuncs(L, base_funcs, 0);

  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "_G");

  lua_pushstring(L, "" "Lua " "5" "." "4");
  lua_setfield(L, -2, "_VERSION");
  return 1;
}
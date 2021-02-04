
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



extern void lua_pushcclosure(lua_State *, lua_CFunction, int);
extern void lua_rotate(lua_State *, int, int);
extern void lua_pushboolean(lua_State *, int);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern void lua_pushvalue(lua_State *, int);
extern int luaL_argerror(lua_State *, int, const char *);
extern int lua_gettop(lua_State *);
extern int io_readline (lua_State *L);

extern void aux_lines (lua_State *L, int toclose) {
  int n = lua_gettop(L) - 1;
  ((void)((n <= 250) || luaL_argerror(L, (250 + 2), ("too many arguments"))));
  lua_pushvalue(L, 1);
  lua_pushinteger(L, n);
  lua_pushboolean(L, toclose);
  lua_rotate(L, 2, 3);
  lua_pushcclosure(L, io_readline, 3 + n);
}
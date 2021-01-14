
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
extern void lua_pushvalue(lua_State *, int);
extern void lua_pushcclosure(lua_State *, lua_CFunction, int);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern int lua_toboolean(lua_State *, int);

extern int iter_auxlax (lua_State *);
extern int iter_auxstrict (lua_State *);

extern int iter_codes (lua_State *L) {
  int lax = lua_toboolean(L, 2);
  (luaL_checklstring(L, (1), ((void*)0)));
  lua_pushcclosure(L, (lax ? iter_auxlax : iter_auxstrict), 0);
  lua_pushvalue(L, 1);
  lua_pushinteger(L, 0);
  return 3;
}
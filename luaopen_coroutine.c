
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

extern int luaB_close(lua_State *);
extern int luaB_yieldable(lua_State *);
extern int luaB_yield(lua_State *);
extern int luaB_cowrap(lua_State *);
extern int luaB_costatus(lua_State *);
extern int luaB_corunning(lua_State *);
extern int luaB_coresume(lua_State *);
extern int luaB_cocreate(lua_State *);

static const luaL_Reg co_funcs[] = {
  {"create", luaB_cocreate},
  {"resume", luaB_coresume},
  {"running", luaB_corunning},
  {"status", luaB_costatus},
  {"wrap", luaB_cowrap},
  {"yield", luaB_yield},
  {"isyieldable", luaB_yieldable},
  {"close", luaB_close},
  {((void*)0), ((void*)0)}
};

extern void luaL_setfuncs(lua_State *, const luaL_Reg *, int);
extern void lua_createtable(lua_State *, int, int);
extern void luaL_checkversion_(lua_State *, lua_Number, size_t);

extern int luaopen_coroutine (lua_State *L) {
  (luaL_checkversion_(L, 504, (sizeof(lua_Integer)*16 + sizeof(lua_Number))), lua_createtable(L, 0, sizeof(co_funcs)/sizeof((co_funcs)[0]) - 1), luaL_setfuncs(L,co_funcs,0));
  return 1;
}
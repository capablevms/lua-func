
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
extern void lua_rawseti(lua_State *, int, lua_Integer);
extern void lua_pushcclosure(lua_State *, lua_CFunction, int);
extern void lua_pushvalue(lua_State *, int);
extern void lua_createtable(lua_State *, int, int);

extern int searcher_preload (lua_State *L);
extern int searcher_Lua (lua_State *L);
extern int searcher_C (lua_State *L);
extern int searcher_Croot (lua_State *L);

static void createsearcherstable (lua_State *L) {
  static const lua_CFunction searchers[] =
    {searcher_preload, searcher_Lua, searcher_C, searcher_Croot, ((void*)0)};
  int i;

  lua_createtable(L, sizeof(searchers)/sizeof(searchers[0]) - 1, 0);

  for (i=0; searchers[i] != ((void*)0); i++) {
    lua_pushvalue(L, -2);
    lua_pushcclosure(L, searchers[i], 1);
    lua_rawseti(L, -2, i+1);
  }
  lua_setfield(L, -2, "searchers");
}

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
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern int lua_getfield(lua_State *, int, const char *);
extern int lua_getfield(lua_State *, int, const char *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

static int searcher_preload (lua_State *L) {
  const char *name = (luaL_checklstring(L, (1), ((void*)0)));
  lua_getfield(L, (-1000000 - 1000), "_PRELOAD");
  if (lua_getfield(L, -1, name) == 0) {
    lua_pushfstring(L, "no field package.preload['%s']", name);
    return 1;
  }
  else {
    lua_pushstring(L, "" ":preload:");
    return 2;
  }
}
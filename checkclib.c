
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

static const char *const CLIBS = "_CLIBS";

extern void lua_settop(lua_State *, int);
extern void * lua_touserdata(lua_State *, int);
extern int lua_getfield(lua_State *, int, const char *);
extern int lua_getfield(lua_State *, int, const char *);

extern void *checkclib (lua_State *L, const char *path) {
  void *plib;
  lua_getfield(L, (-1000000 - 1000), CLIBS);
  lua_getfield(L, -1, path);
  plib = lua_touserdata(L, -1);
  lua_settop(L, -(2)-1);
  return plib;
}

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



extern const char * searchpath(lua_State *, const char *, const char *, const char *, const char *);
extern int luaL_error(lua_State *, const char *, ...);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern int lua_getfield(lua_State *, int, const char *);

static const char *findfile (lua_State *L, const char *name,
                                           const char *pname,
                                           const char *dirsep) {
  const char *path;
  lua_getfield(L, ((-1000000 - 1000) - (1)), pname);
  path = lua_tolstring(L, (-1), ((void*)0));
  if (path == ((void*)0))
    luaL_error(L, "'package.%s' must be a string", pname);
  return searchpath(L, name, path, ".", dirsep);
}
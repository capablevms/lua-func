
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



extern int luaL_error(lua_State *, const char *, ...);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern int pushglobalfuncname(lua_State *, lua_Debug *);
extern int luaL_error(lua_State *, const char *, ...);
extern int strcmp(const char *, const char *);
extern int lua_getinfo(lua_State *, const char *, lua_Debug *);
extern int luaL_error(lua_State *, const char *, ...);
extern int lua_getstack(lua_State *, int, lua_Debug *);

extern int luaL_argerror (lua_State *L, int arg, const char *extramsg) {
  lua_Debug ar;
  if (!lua_getstack(L, 0, &ar))
    return luaL_error(L, "bad argument #%d (%s)", arg, extramsg);
  lua_getinfo(L, "n", &ar);
  if (strcmp(ar.namewhat, "method") == 0) {
    arg--;
    if (arg == 0)
      return luaL_error(L, "calling '%s' on bad self (%s)",
                           ar.name, extramsg);
  }
  if (ar.name == ((void*)0))
    ar.name = (pushglobalfuncname(L, &ar)) ? lua_tolstring(L, (-1), ((void*)0)) : "?";
  return luaL_error(L, "bad argument #%d to '%s' (%s)",
                        arg, ar.name, extramsg);
}
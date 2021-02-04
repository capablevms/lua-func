
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
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern const char * lua_pushstring(lua_State *, const char *);

extern int checkload (lua_State *L, int stat, const char *filename) {
  if (stat) {
    lua_pushstring(L, filename);
    return 2;
  }
  else
    return luaL_error(L, "error loading module '%s' from file '%s':\n\t%s",
                          lua_tolstring(L, (1), ((void*)0)), filename, lua_tolstring(L, (-1), ((void*)0)));
}
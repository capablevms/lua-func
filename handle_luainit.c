
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



extern int dostring(lua_State *, const char *, const char *);
extern int dofile(lua_State *, const char *);
extern char * getenv(const char *);
extern char * getenv(const char *);

static int handle_luainit (lua_State *L) {
  const char *name = "=" "LUA_INIT" "_" "5" "_" "4";
  const char *init = getenv(name + 1);
  if (init == ((void*)0)) {
    name = "=" "LUA_INIT";
    init = getenv(name + 1);
  }
  if (init == ((void*)0)) return 0;
  else if (init[0] == '@')
    return dofile(L, init+1);
  else
    return dostring(L, init, name);
}
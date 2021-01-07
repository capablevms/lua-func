
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



extern int luaL_argerror(lua_State *, int, const char *);
extern lua_Integer luaL_checkinteger(lua_State *, int);

static time_t l_checktime (lua_State *L, int arg) {
  lua_Integer t = luaL_checkinteger(L, arg);
  ((void)(((time_t)t == t) || luaL_argerror(L, (arg), ("time out-of-bounds"))));
  return (time_t)t;
}
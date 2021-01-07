
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



extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern int luaL_argerror(lua_State *, int, const char *);
extern lua_Integer luaL_checkinteger(lua_State *, int);

static void pushutfchar (lua_State *L, int arg) {
  lua_Unsigned code = (lua_Unsigned)luaL_checkinteger(L, arg);
  ((void)((code <= 0x7FFFFFFFu) || luaL_argerror(L, (arg), ("value out of range"))));
  lua_pushfstring(L, "%U", (long)code);
}
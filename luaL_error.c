
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



extern int lua_error(lua_State *);
extern void lua_concat(lua_State *, int);
extern const char * lua_pushvfstring(lua_State *, const char *, va_list);
extern void luaL_where(lua_State *, int);

extern int luaL_error (lua_State *L, const char *fmt, ...) {
  va_list argp;
  __builtin_va_start(argp, fmt);
  luaL_where(L, 1);
  lua_pushvfstring(L, fmt, argp);
  __builtin_va_end(argp);
  lua_concat(L, 2);
  return lua_error(L);
}

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



extern void luaL_traceback(lua_State *, lua_State *, const char *, int);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern void lua_pushvalue(lua_State *, int);
extern int lua_type(lua_State *, int);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern lua_State * getthread(lua_State *, int *);

static int db_traceback (lua_State *L) {
  int arg;
  lua_State *L1 = getthread(L, &arg);
  const char *msg = lua_tolstring(L, (arg + 1), ((void*)0));
  if (msg == ((void*)0) && !(lua_type(L, (arg + 1)) <= 0))
    lua_pushvalue(L, arg + 1);
  else {
    int level = (int)luaL_optinteger(L, arg + 2, (L == L1) ? 1 : 0);
    luaL_traceback(L, L1, msg, level);
  }
  return 1;
}
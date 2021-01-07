
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



extern void lua_close(lua_State *);
extern int report(lua_State *, int);
extern int lua_toboolean(lua_State *, int);
extern int lua_pcallk(lua_State *, int, int, int, lua_KContext, lua_KFunction);
extern void lua_pushlightuserdata(lua_State *, void *);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern void lua_pushcclosure(lua_State *, lua_CFunction, int);
extern void l_message(const char *, const char *);
extern lua_State * luaL_newstate();

int main (int argc, char **argv) {
  int status, result;
  lua_State *L = luaL_newstate();
  if (L == ((void*)0)) {
    l_message(argv[0], "cannot create state: not enough memory");
    return 1;
  }
  lua_pushcclosure(L, (&pmain), 0);
  lua_pushinteger(L, argc);
  lua_pushlightuserdata(L, argv);
  status = lua_pcallk(L, (2), (1), (0), 0, ((void*)0));
  result = lua_toboolean(L, -1);
  report(L, status);
  lua_close(L);
  return (result && status == 0) ? 0 : 1;
}
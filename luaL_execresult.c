
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



extern void lua_pushinteger(lua_State *, lua_Integer);
extern const char * lua_pushstring(lua_State *, const char *);
extern void lua_pushnil(lua_State *);
extern void lua_pushboolean(lua_State *, int);
extern int luaL_fileresult(lua_State *, int, const char *);
extern int * __errno_location();

extern int luaL_execresult (lua_State *L, int stat) {
  const char *what = "exit";
  if (stat != 0 && (*__errno_location ()) != 0)
    return luaL_fileresult(L, 0, ((void*)0));
  else {
                             ;
    if (*what == 'e' && stat == 0)
      lua_pushboolean(L, 1);
    else
      lua_pushnil(L);
    lua_pushstring(L, what);
    lua_pushinteger(L, stat);
    return 3;
  }
}
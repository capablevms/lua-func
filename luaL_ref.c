
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



extern void lua_rawseti(lua_State *, int, lua_Integer);
extern lua_Unsigned lua_rawlen(lua_State *, int);
extern void lua_rawseti(lua_State *, int, lua_Integer);
extern int lua_rawgeti(lua_State *, int, lua_Integer);
extern void lua_settop(lua_State *, int);
extern lua_Integer lua_tointegerx(lua_State *, int, int *);
extern int lua_rawgeti(lua_State *, int, lua_Integer);
extern int lua_absindex(lua_State *, int);
extern void lua_settop(lua_State *, int);
extern int lua_type(lua_State *, int);

extern int luaL_ref (lua_State *L, int t) {
  int ref;
  if ((lua_type(L, (-1)) == 0)) {
    lua_settop(L, -(1)-1);
    return (-1);
  }
  t = lua_absindex(L, t);
  lua_rawgeti(L, t, 0);
  ref = (int)lua_tointegerx(L,(-1),((void*)0));
  lua_settop(L, -(1)-1);
  if (ref != 0) {
    lua_rawgeti(L, t, ref);
    lua_rawseti(L, t, 0);
  }
  else
    ref = (int)lua_rawlen(L, t) + 1;
  lua_rawseti(L, t, ref);
  return ref;
}
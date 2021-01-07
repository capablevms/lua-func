
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
extern void lua_rotate(lua_State *, int, int);
extern void luaL_where(lua_State *, int);
extern int lua_type(lua_State *, int);
extern int lua_resetthread(lua_State *);
extern int lua_status(lua_State *);
extern int auxresume(lua_State *, lua_State *, int);
extern int lua_gettop(lua_State *);
extern lua_State * lua_tothread(lua_State *, int);

static int luaB_auxwrap (lua_State *L) {
  lua_State *co = lua_tothread(L, ((-1000000 - 1000) - (1)));
  int r = auxresume(L, co, lua_gettop(L));
  if (r < 0) {
    int stat = lua_status(co);
    if (stat != 0 && stat != 1)
      lua_resetthread(co);
    if (stat != 4 &&
        lua_type(L, -1) == 4) {
      luaL_where(L, 1);
      lua_rotate(L, (-2), 1);
      lua_concat(L, 2);
    }
    return lua_error(L);
  }
  return r;
}
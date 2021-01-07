
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



extern void luaL_pushresult(luaL_Buffer *);
extern int luaL_error(lua_State *, const char *, ...);
extern int lua_dump(lua_State *, lua_Writer, void *, int);
extern void lua_settop(lua_State *, int);
extern void luaL_checktype(lua_State *, int, int);
extern int lua_toboolean(lua_State *, int);

static int str_dump (lua_State *L) {
  struct str_Writer state;
  int strip = lua_toboolean(L, 2);
  luaL_checktype(L, 1, 6);
  lua_settop(L, 1);
  state.init = 0;
  if (lua_dump(L, writer, &state, strip) != 0)
    return luaL_error(L, "unable to dump given function");
  luaL_pushresult(&state.B);
  return 1;
}
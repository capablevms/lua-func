
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



extern void lua_setfield(lua_State *, int, const char *);
extern void lua_pushvalue(lua_State *, int);
extern void lua_createtable(lua_State *, int, int);
extern int lua_absindex(lua_State *, int);
extern void lua_settop(lua_State *, int);
extern int lua_getfield(lua_State *, int, const char *);

extern int luaL_getsubtable (lua_State *L, int idx, const char *fname) {
  if (lua_getfield(L, idx, fname) == 5)
    return 1;
  else {
    lua_settop(L, -(1)-1);
    idx = lua_absindex(L, idx);
    lua_createtable(L, 0, 0);
    lua_pushvalue(L, -1);
    lua_setfield(L, idx, fname);
    return 0;
  }
}

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

typedef unsigned int IdxT;

extern void set2(lua_State *, IdxT, IdxT);
extern void set2(lua_State *, IdxT, IdxT);
extern void lua_settop(lua_State *, int);
extern void lua_settop(lua_State *, int);
extern int luaL_error(lua_State *, const char *, ...);
extern int sort_comp(lua_State *, int, int);
extern int lua_geti(lua_State *, int, lua_Integer);
extern void lua_settop(lua_State *, int);
extern int luaL_error(lua_State *, const char *, ...);
extern int sort_comp(lua_State *, int, int);
extern int lua_geti(lua_State *, int, lua_Integer);

static IdxT partition (lua_State *L, IdxT lo, IdxT up) {
  IdxT i = lo;
  IdxT j = up - 1;

  for (;;) {

    while ((void)lua_geti(L, 1, ++i), sort_comp(L, -1, -2)) {
      if (i == up - 1)
        luaL_error(L, "invalid order function for sorting");
      lua_settop(L, -(1)-1);
    }


    while ((void)lua_geti(L, 1, --j), sort_comp(L, -3, -1)) {
      if (j < i)
        luaL_error(L, "invalid order function for sorting");
      lua_settop(L, -(1)-1);
    }

    if (j < i) {

      lua_settop(L, -(1)-1);

      set2(L, up - 1, i);
      return i;
    }

    set2(L, i, j);
  }
}
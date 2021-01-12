
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

extern unsigned int l_randomizePivot();
extern IdxT partition(lua_State *, IdxT, IdxT);
extern void set2(lua_State *, IdxT, IdxT);
extern int lua_geti(lua_State *, int, lua_Integer);
extern void lua_pushvalue(lua_State *, int);
extern void lua_settop(lua_State *, int);
extern void set2(lua_State *, IdxT, IdxT);
extern int sort_comp(lua_State *, int, int);
extern void lua_settop(lua_State *, int);
extern IdxT choosePivot(IdxT, IdxT, unsigned int);

static void auxsort (lua_State *L, IdxT lo, IdxT up,
                                   unsigned int rnd) {
  while (lo < up) {
    IdxT p;
    IdxT n;

    lua_geti(L, 1, lo);
    lua_geti(L, 1, up);
    if (sort_comp(L, -1, -2))
      set2(L, lo, up);
    else
      lua_settop(L, -(2)-1);
    if (up - lo == 1)
      return;
    if (up - lo < 100u || rnd == 0)
      p = (lo + up)/2;
    else
      p = choosePivot(lo, up, rnd);
    lua_geti(L, 1, p);
    lua_geti(L, 1, lo);
    if (sort_comp(L, -2, -1))
      set2(L, p, lo);
    else {
      lua_settop(L, -(1)-1);
      lua_geti(L, 1, up);
      if (sort_comp(L, -1, -2))
        set2(L, p, up);
      else
        lua_settop(L, -(2)-1);
    }
    if (up - lo == 2)
      return;
    lua_geti(L, 1, p);
    lua_pushvalue(L, -1);
    lua_geti(L, 1, up - 1);
    set2(L, p, up - 1);
    p = partition(L, lo, up);

    if (p - lo < up - p) {
      auxsort(L, lo, p - 1, rnd);
      n = p - lo;
      lo = p + 1;
    }
    else {
      auxsort(L, p + 1, up, rnd);
      n = up - p;
      up = p - 1;
    }
    if ((up - lo) / 128 > n)
      rnd = l_randomizePivot();
  }
}

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

extern void checktab(lua_State *, int, int);

extern int tmove (lua_State *L) {
  lua_Integer f = luaL_checkinteger(L, 2);
  lua_Integer e = luaL_checkinteger(L, 3);
  lua_Integer t = luaL_checkinteger(L, 4);
  int tt = !(lua_type(L, (5)) <= 0) ? 5 : 1;
  checktab(L, 1, 1);
  checktab(L, tt, 2);
  if (e >= f) {
    lua_Integer n, i;
    ((void)((f > 0 || e < 9223372036854775807LL + f) || luaL_argerror(L, (3), ("too many elements to move"))));

    n = e - f + 1;
    ((void)((t <= 9223372036854775807LL - n + 1) || luaL_argerror(L, (4), ("destination wrap around"))));

    if (t > e || t <= f || (tt != 1 && !lua_compare(L, 1, tt, 0))) {
      for (i = 0; i < n; i++) {
        lua_geti(L, 1, f + i);
        lua_seti(L, tt, t + i);
      }
    }
    else {
      for (i = n - 1; i >= 0; i--) {
        lua_geti(L, 1, f + i);
        lua_seti(L, tt, t + i);
      }
    }
  }
  lua_pushvalue(L, tt);
  return 1;
}


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

lua_Integer luaV_idiv (lua_State *L, lua_Integer m, lua_Integer n) {
  if ((__builtin_expect(((((lua_Unsigned)(n)) + 1u <= 1u) != 0), 0))) {
    if (n == 0)
      luaG_runerror(L, "attempt to divide by zero");
    return ((lua_Integer)(((lua_Unsigned)(0)) - ((lua_Unsigned)(m))));
  }
  else {
    lua_Integer q = m / n;
    if ((m ^ n) < 0 && m % n != 0)
      q -= 1;
    return q;
  }
}

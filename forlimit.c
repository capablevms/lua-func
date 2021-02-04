
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

extern int forlimit (lua_State *L, lua_Integer init, const TValue *lim,
                                   lua_Integer *p, lua_Integer step) {
  if (!luaV_tointeger(lim, p, (step < 0 ? F2Iceil : F2Ifloor))) {

    lua_Number flim;
    if (!(((((lim))->tt_) == (((3) | ((1) << 4)))) ? (*(&flim) = (((lim)->value_).n), 1) : luaV_tonumber_(lim,&flim)))
      luaG_forerror(L, lim, "limit");

    if (((0)<(flim))) {
      if (step < 0) return 1;
      *p = 9223372036854775807LL;
    }
    else {
      if (step > 0) return 1;
      *p = (-9223372036854775807LL -1LL);
    }
  }
  return (step > 0 ? init > *p : init < *p);
}

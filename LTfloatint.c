
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

extern int LTfloatint (lua_Number f, lua_Integer i) {
  if (((((lua_Unsigned)1 << ((53))) + ((lua_Unsigned)(i))) <= (2 * ((lua_Unsigned)1 << ((53))))))
    return ((f)<(((lua_Number)((i)))));
  else {
    lua_Integer fi;
    if (luaV_flttointeger(f, &fi, F2Ifloor))
      return fi < i;
    else
      return f < 0;
  }
}

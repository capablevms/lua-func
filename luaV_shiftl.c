
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

lua_Integer luaV_shiftl (lua_Integer x, lua_Integer y) {
  if (y < 0) {
    if (y <= -((int)((sizeof(lua_Integer) * 8)))) return 0;
    else return ((lua_Integer)(((lua_Unsigned)(x)) >> ((lua_Unsigned)(-y))));
  }
  else {
    if (y >= ((int)((sizeof(lua_Integer) * 8)))) return 0;
    else return ((lua_Integer)(((lua_Unsigned)(x)) << ((lua_Unsigned)(y))));
  }
}

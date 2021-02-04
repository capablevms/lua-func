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

static int checkfield (lua_State *L, const char *key, int n) {
  lua_pushstring(L, key);
  return (lua_rawget(L, -n) != 0);
}

extern void checktab (lua_State *L, int arg, int what) {
  if (lua_type(L, arg) != 5) {
    int n = 1;
    if (lua_getmetatable(L, arg) &&
        (!(what & 1) || checkfield(L, "__index", ++n)) &&
        (!(what & 2) || checkfield(L, "__newindex", ++n)) &&
        (!(what & 4) || checkfield(L, "__len", ++n))) {
      lua_settop(L, -(n)-1);
    }
    else
      luaL_checktype(L, arg, 5);
  }
}


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

extern void checktab (lua_State *, int, int);

extern int tinsert (lua_State *L) {
  lua_Integer e = (checktab(L, 1, ((1 | 2)) | 4), luaL_len(L, 1)) + 1;
  lua_Integer pos;
  switch (lua_gettop(L)) {
    case 2: {
      pos = e;
      break;
    }
    case 3: {
      lua_Integer i;
      pos = luaL_checkinteger(L, 2);

      ((void)(((lua_Unsigned)pos - 1u < (lua_Unsigned)e) || luaL_argerror(L, (2), ("position out of bounds"))));

      for (i = e; i > pos; i--) {
        lua_geti(L, 1, i - 1);
        lua_seti(L, 1, i);
      }
      break;
    }
    default: {
      return luaL_error(L, "wrong number of arguments to 'insert'");
    }
  }
  lua_seti(L, 1, pos);
  return 0;
}

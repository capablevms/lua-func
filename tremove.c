
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

extern int tremove (lua_State *L) {
  lua_Integer size = (checktab(L, 1, ((1 | 2)) | 4), luaL_len(L, 1));
  lua_Integer pos = luaL_optinteger(L, 2, size);
  if (pos != size)

    ((void)(((lua_Unsigned)pos - 1u <= (lua_Unsigned)size) || luaL_argerror(L, (1), ("position out of bounds"))));

  lua_geti(L, 1, pos);
  for ( ; pos < size; pos++) {
    lua_geti(L, 1, pos + 1);
    lua_seti(L, 1, pos);
  }
  lua_pushnil(L);
  lua_seti(L, 1, pos);
  return 1;
}

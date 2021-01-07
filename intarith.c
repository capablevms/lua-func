
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



extern lua_Integer luaV_shiftl(lua_Integer, lua_Integer);
extern lua_Integer luaV_shiftl(lua_Integer, lua_Integer);
extern lua_Integer luaV_idiv(lua_State *, lua_Integer, lua_Integer);
extern lua_Integer luaV_mod(lua_State *, lua_Integer, lua_Integer);

static lua_Integer intarith (lua_State *L, int op, lua_Integer v1,
                                                   lua_Integer v2) {
  switch (op) {
    case 0: return ((lua_Integer)(((lua_Unsigned)(v1)) + ((lua_Unsigned)(v2))));
    case 1:return ((lua_Integer)(((lua_Unsigned)(v1)) - ((lua_Unsigned)(v2))));
    case 2:return ((lua_Integer)(((lua_Unsigned)(v1)) * ((lua_Unsigned)(v2))));
    case 3: return luaV_mod(L, v1, v2);
    case 6: return luaV_idiv(L, v1, v2);
    case 7: return ((lua_Integer)(((lua_Unsigned)(v1)) & ((lua_Unsigned)(v2))));
    case 8: return ((lua_Integer)(((lua_Unsigned)(v1)) | ((lua_Unsigned)(v2))));
    case 9: return ((lua_Integer)(((lua_Unsigned)(v1)) ^ ((lua_Unsigned)(v2))));
    case 10: return luaV_shiftl(v1, v2);
    case 11: return luaV_shiftl(v1, -v2);
    case 12: return ((lua_Integer)(((lua_Unsigned)(0)) - ((lua_Unsigned)(v1))));
    case 13: return ((lua_Integer)(((lua_Unsigned)(~((lua_Unsigned)(0)))) ^ ((lua_Unsigned)(v1))));
    default: ((void)0); return 0;
  }
}
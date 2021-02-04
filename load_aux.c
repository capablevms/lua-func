
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



extern void lua_rotate(lua_State *, int, int);
extern void lua_pushnil(lua_State *);
extern void lua_settop(lua_State *, int);
extern const char * lua_setupvalue(lua_State *, int, int);
extern void lua_pushvalue(lua_State *, int);

extern int load_aux (lua_State *L, int status, int envidx) {
  if (status == 0) {
    if (envidx != 0) {
      lua_pushvalue(L, envidx);
      if (!lua_setupvalue(L, -2, 1))
        lua_settop(L, -(1)-1);
    }
    return 1;
  }
  else {
    lua_pushnil(L);
    lua_rotate(L, (-2), 1);
    return 2;
  }
}
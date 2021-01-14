
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



extern void lua_settop(lua_State *, int);
extern void lua_concat(lua_State *, int);
extern void lua_settop(lua_State *, int);
extern void lua_copy(lua_State *, int, int);
extern const char * lua_pushstring(lua_State *, const char *);
extern void lua_settop(lua_State *, int);
extern int lua_rawequal(lua_State *, int, int);
extern int lua_type(lua_State *, int);
extern int lua_next(lua_State *, int);
extern void lua_pushnil(lua_State *);
extern int lua_type(lua_State *, int);

extern int findfield (lua_State *L, int objidx, int level) {
  if (level == 0 || !(lua_type(L, (-1)) == 5))
    return 0;
  lua_pushnil(L);
  while (lua_next(L, -2)) {
    if (lua_type(L, -2) == 4) {
      if (lua_rawequal(L, objidx, -1)) {
        lua_settop(L, -(1)-1);
        return 1;
      }
      else if (findfield(L, objidx, level - 1)) {

        lua_pushstring(L, "" ".");
        (lua_copy(L, -1, (-3)), lua_settop(L, -(1)-1));
        lua_concat(L, 3);
        return 1;
      }
    }
    lua_settop(L, -(1)-1);
  }
  return 0;
}
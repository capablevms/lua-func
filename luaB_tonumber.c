
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



extern void lua_pushnil(lua_State *);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern const char * b_str2int(const char *, int, lua_Integer *);
extern int luaL_argerror(lua_State *, int, const char *);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern void luaL_checktype(lua_State *, int, int);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern void luaL_checkany(lua_State *, int);
extern size_t lua_stringtonumber(lua_State *, const char *);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern void lua_settop(lua_State *, int);
extern int lua_type(lua_State *, int);
extern int lua_type(lua_State *, int);

static int luaB_tonumber (lua_State *L) {
  if ((lua_type(L, (2)) <= 0)) {
    if (lua_type(L, 1) == 3) {
      lua_settop(L, 1);
      return 1;
    }
    else {
      size_t l;
      const char *s = lua_tolstring(L, 1, &l);
      if (s != ((void*)0) && lua_stringtonumber(L, s) == l + 1)
        return 1;

      luaL_checkany(L, 1);
    }
  }
  else {
    size_t l;
    const char *s;
    lua_Integer n = 0;
    lua_Integer base = luaL_checkinteger(L, 2);
    luaL_checktype(L, 1, 4);
    s = lua_tolstring(L, 1, &l);
    ((void)((2 <= base && base <= 36) || luaL_argerror(L, (2), ("base out of range"))));
    if (b_str2int(s, (int)base, &n) == s + l) {
      lua_pushinteger(L, n);
      return 1;
    }
  }
  lua_pushnil(L);
  return 1;
}
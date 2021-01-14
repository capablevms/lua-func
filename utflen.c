
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

typedef unsigned int utfint;


extern void lua_pushinteger(lua_State *, lua_Integer);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern void lua_pushnil(lua_State *);
extern const char * utf8_decode(const char *, utfint *, int);
extern int luaL_argerror(lua_State *, int, const char *);
extern int luaL_argerror(lua_State *, int, const char *);
extern int lua_toboolean(lua_State *, int);
extern lua_Integer u_posrelat(lua_Integer, size_t);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern lua_Integer u_posrelat(lua_Integer, size_t);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

extern int utflen (lua_State *L) {
  lua_Integer n = 0;
  size_t len;
  const char *s = luaL_checklstring(L, 1, &len);
  lua_Integer posi = u_posrelat(luaL_optinteger(L, 2, 1), len);
  lua_Integer posj = u_posrelat(luaL_optinteger(L, 3, -1), len);
  int lax = lua_toboolean(L, 4);
  ((void)((1 <= posi && --posi <= (lua_Integer)len) || luaL_argerror(L, (2), ("initial position out of bounds"))));

  ((void)((--posj < (lua_Integer)len) || luaL_argerror(L, (3), ("final position out of bounds"))));

  while (posi <= posj) {
    const char *s1 = utf8_decode(s + posi, ((void*)0), !lax);
    if (s1 == ((void*)0)) {
      lua_pushnil(L);
      lua_pushinteger(L, posi + 1);
      return 2;
    }
    posi = s1 - s;
    n++;
  }
  lua_pushinteger(L, n);
  return 1;
}
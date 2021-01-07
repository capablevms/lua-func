
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
extern int luaL_error(lua_State *, const char *, ...);
extern const char * utf8_decode(const char *, utfint *, int);
extern void luaL_checkstack(lua_State *, int, const char *);
extern int luaL_error(lua_State *, const char *, ...);
extern int luaL_argerror(lua_State *, int, const char *);
extern int luaL_argerror(lua_State *, int, const char *);
extern int lua_toboolean(lua_State *, int);
extern lua_Integer u_posrelat(lua_Integer, size_t);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern lua_Integer u_posrelat(lua_Integer, size_t);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

static int codepoint (lua_State *L) {
  size_t len;
  const char *s = luaL_checklstring(L, 1, &len);
  lua_Integer posi = u_posrelat(luaL_optinteger(L, 2, 1), len);
  lua_Integer pose = u_posrelat(luaL_optinteger(L, 3, posi), len);
  int lax = lua_toboolean(L, 4);
  int n;
  const char *se;
  ((void)((posi >= 1) || luaL_argerror(L, (2), ("out of bounds"))));
  ((void)((pose <= (lua_Integer)len) || luaL_argerror(L, (3), ("out of bounds"))));
  if (posi > pose) return 0;
  if (pose - posi >= 2147483647)
    return luaL_error(L, "string slice too long");
  n = (int)(pose - posi) + 1;
  luaL_checkstack(L, n, "string slice too long");
  n = 0;
  se = s + pose;
  for (s += posi - 1; s < se;) {
    utfint code;
    s = utf8_decode(s, &code, !lax);
    if (s == ((void*)0))
      return luaL_error(L, "invalid UTF-8 code");
    lua_pushinteger(L, code);
    n++;
  }
  return n;
}
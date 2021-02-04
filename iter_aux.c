
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
extern int luaL_error(lua_State *, const char *, ...);
extern const char * utf8_decode(const char *, utfint *, int);
extern lua_Integer lua_tointegerx(lua_State *, int, int *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

extern int iter_aux (lua_State *L, int strict) {
  size_t len;
  const char *s = luaL_checklstring(L, 1, &len);
  lua_Integer n = lua_tointegerx(L,(2),((void*)0)) - 1;
  if (n < 0)
    n = 0;
  else if (n < (lua_Integer)len) {
    n++;
    while (((*(s + n) & 0xC0) == 0x80)) n++;
  }
  if (n >= (lua_Integer)len)
    return 0;
  else {
    utfint code;
    const char *next = utf8_decode(s + n, &code, strict);
    if (next == ((void*)0))
      return luaL_error(L, "invalid UTF-8 code");
    lua_pushinteger(L, n + 1);
    lua_pushinteger(L, code);
    return 2;
  }
}
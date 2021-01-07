
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
extern int luaL_error(lua_State *, const char *, ...);
extern int luaL_argerror(lua_State *, int, const char *);
extern lua_Integer u_posrelat(lua_Integer, size_t);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

static int byteoffset (lua_State *L) {
  size_t len;
  const char *s = luaL_checklstring(L, 1, &len);
  lua_Integer n = luaL_checkinteger(L, 2);
  lua_Integer posi = (n >= 0) ? 1 : len + 1;
  posi = u_posrelat(luaL_optinteger(L, 3, posi), len);
  ((void)((1 <= posi && --posi <= (lua_Integer)len) || luaL_argerror(L, (3), ("position out of bounds"))));

  if (n == 0) {

    while (posi > 0 && ((*(s + posi) & 0xC0) == 0x80)) posi--;
  }
  else {
    if (((*(s + posi) & 0xC0) == 0x80))
      return luaL_error(L, "initial position is a continuation byte");
    if (n < 0) {
       while (n < 0 && posi > 0) {
         do {
           posi--;
         } while (posi > 0 && ((*(s + posi) & 0xC0) == 0x80));
         n++;
       }
     }
     else {
       n--;
       while (n > 0 && posi < (lua_Integer)len) {
         do {
           posi++;
         } while (((*(s + posi) & 0xC0) == 0x80));
         n--;
       }
     }
  }
  if (n == 0)
    lua_pushinteger(L, posi + 1);
  else
    lua_pushnil(L);
  return 1;
}
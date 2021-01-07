
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



extern int luaL_argerror(lua_State *, int, const char *);
extern void luaL_addvalue(luaL_Buffer *);
extern const char * luaL_tolstring(lua_State *, int, size_t *);
extern int snprintf(char *restrict, size_t, const char *restrict, ...);
extern lua_Integer lua_tointegerx(lua_State *, int, int *);
extern int quotefloat(lua_State *, char *, lua_Number);
extern lua_Number lua_tonumberx(lua_State *, int, int *);
extern int lua_isinteger(lua_State *, int);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern void addquoted(luaL_Buffer *, const char *, size_t);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern int lua_type(lua_State *, int);

static void addliteral (lua_State *L, luaL_Buffer *b, int arg) {
  switch (lua_type(L, arg)) {
    case 4: {
      size_t len;
      const char *s = lua_tolstring(L, arg, &len);
      addquoted(b, s, len);
      break;
    }
    case 3: {
      char *buff = luaL_prepbuffsize(b, 120);
      int nb;
      if (!lua_isinteger(L, arg))
        nb = quotefloat(L, buff, lua_tonumberx(L,(arg),((void*)0)));
      else {
        lua_Integer n = lua_tointegerx(L,(arg),((void*)0));
        const char *format = (n == (-9223372036854775807LL -1LL))
                           ? "0x%" "ll" "x"
                           : "%" "ll" "d";
        nb = snprintf(buff,120,format,(long long)n);
      }
      ((b)->n += (nb));
      break;
    }
    case 0: case 1: {
      luaL_tolstring(L, arg, ((void*)0));
      luaL_addvalue(b);
      break;
    }
    default: {
      luaL_argerror(L, arg, "value has no literal form");
    }
  }
}
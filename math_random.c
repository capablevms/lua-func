
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

typedef struct {
  unsigned long s[4];
} RanState;


extern void lua_pushinteger(lua_State *, lua_Integer);
extern lua_Unsigned project(lua_Unsigned, lua_Unsigned, RanState *);
extern int luaL_argerror(lua_State *, int, const char *);
extern int luaL_error(lua_State *, const char *, ...);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern void lua_pushnumber(lua_State *, lua_Number);
extern lua_Number I2d(unsigned long);
extern int lua_gettop(lua_State *);
extern unsigned long nextrand(unsigned long *);
extern void * lua_touserdata(lua_State *, int);

static int math_random (lua_State *L) {
  lua_Integer low, up;
  lua_Unsigned p;
  RanState *state = (RanState *)lua_touserdata(L, ((-1000000 - 1000) - (1)));
  unsigned long rv = nextrand(state->s);
  switch (lua_gettop(L)) {
    case 0: {
      lua_pushnumber(L, I2d(rv));
      return 1;
    }
    case 1: {
      low = 1;
      up = luaL_checkinteger(L, 1);
      if (up == 0) {
        lua_pushinteger(L, ((lua_Unsigned)((rv) & 0xffffffffffffffffu)));
        return 1;
      }
      break;
    }
    case 2: {
      low = luaL_checkinteger(L, 1);
      up = luaL_checkinteger(L, 2);
      break;
    }
    default: return luaL_error(L, "wrong number of arguments");
  }

  ((void)((low <= up) || luaL_argerror(L, (1), ("interval is empty"))));

  p = project(((lua_Unsigned)((rv) & 0xffffffffffffffffu)), (lua_Unsigned)up - (lua_Unsigned)low, state);
  lua_pushinteger(L, p + (lua_Unsigned)low);
  return 1;
}
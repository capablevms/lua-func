
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


extern void setseed(lua_State *, unsigned long *, lua_Unsigned, lua_Unsigned);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern void randseed(lua_State *, RanState *);
extern int lua_type(lua_State *, int);
extern void * lua_touserdata(lua_State *, int);

extern int math_randomseed (lua_State *L) {
  RanState *state = (RanState *)lua_touserdata(L, ((-1000000 - 1000) - (1)));
  if ((lua_type(L, (1)) == (-1))) {
    randseed(L, state);
  }
  else {
    lua_Integer n1 = luaL_checkinteger(L, 1);
    lua_Integer n2 = luaL_optinteger(L, 2, 0);
    setseed(L, state->s, n1, n2);
  }
  return 2;
}
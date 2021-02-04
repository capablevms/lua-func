
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

extern const luaL_Reg randfuncs[];

extern void luaL_setfuncs(lua_State *, const luaL_Reg *, int);
extern void lua_settop(lua_State *, int);
extern void randseed(lua_State *, RanState *);
extern void * lua_newuserdatauv(lua_State *, size_t, int);

extern void setrandfunc (lua_State *L) {
  RanState *state = (RanState *)lua_newuserdatauv(L, sizeof(RanState), 0);
  randseed(L, state);
  lua_settop(L, -(2)-1);
  luaL_setfuncs(L, randfuncs, 1);
}
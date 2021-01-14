
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



extern void lua_pushinteger(lua_State *, lua_Integer);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern unsigned long nextrand(unsigned long *);

extern void setseed (lua_State *L, unsigned long *state,
                     lua_Unsigned n1, lua_Unsigned n2) {
  int i;
  state[0] = ((unsigned long)(n1));
  state[1] = ((unsigned long)(0xff));
  state[2] = ((unsigned long)(n2));
  state[3] = ((unsigned long)(0));
  for (i = 0; i < 16; i++)
    nextrand(state);
  lua_pushinteger(L, n1);
  lua_pushinteger(L, n2);
}
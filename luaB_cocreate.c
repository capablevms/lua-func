
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



extern void lua_xmove(lua_State *, lua_State *, int);
extern void lua_pushvalue(lua_State *, int);
extern lua_State * lua_newthread(lua_State *);
extern void luaL_checktype(lua_State *, int, int);

extern int luaB_cocreate (lua_State *L) {
  lua_State *NL;
  luaL_checktype(L, 1, 6);
  NL = lua_newthread(L);
  lua_pushvalue(L, 1);
  lua_xmove(L, NL, 1);
  return 1;
}
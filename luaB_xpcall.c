
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



extern int finishpcall(lua_State *, int, lua_KContext);
extern int lua_pcallk(lua_State *, int, int, int, lua_KContext, lua_KFunction);
extern void lua_rotate(lua_State *, int, int);
extern void lua_pushvalue(lua_State *, int);
extern void lua_pushboolean(lua_State *, int);
extern void luaL_checktype(lua_State *, int, int);
extern int lua_gettop(lua_State *);

static int luaB_xpcall (lua_State *L) {
  int status;
  int n = lua_gettop(L);
  luaL_checktype(L, 2, 6);
  lua_pushboolean(L, 1);
  lua_pushvalue(L, 1);
  lua_rotate(L, 3, 2);
  status = lua_pcallk(L, n - 2, (-1), 2, 2, finishpcall);
  return finishpcall(L, status, 2);
}
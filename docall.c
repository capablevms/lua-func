
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

static lua_State *globalL = ((void*)0);

extern void lua_settop(lua_State *, int);
extern void lua_rotate(lua_State *, int, int);
extern __sighandler_t signal(int, __sighandler_t);
extern int lua_pcallk(lua_State *, int, int, int, lua_KContext, lua_KFunction);
extern __sighandler_t signal(int, __sighandler_t);
extern void lua_rotate(lua_State *, int, int);
extern void lua_pushcclosure(lua_State *, lua_CFunction, int);
extern int lua_gettop(lua_State *);

extern int msghandler (lua_State *);
extern void laction (int i);

static int docall (lua_State *L, int narg, int nres) {
  int status;
  int base = lua_gettop(L) - narg;
  lua_pushcclosure(L, (msghandler), 0);
  lua_rotate(L, (base), 1);
  globalL = L;
  signal(2, laction);
  status = lua_pcallk(L, (narg), (nres), (base), 0, ((void*)0));
  signal(2, ((__sighandler_t) 0));
  (lua_rotate(L, (base), -1), lua_settop(L, -(1)-1));
  return status;
}
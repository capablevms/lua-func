
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
extern void * lua_upvalueid(lua_State *, int, int);
extern void luaL_checktype(lua_State *, int, int);
extern lua_Integer luaL_checkinteger(lua_State *, int);

static void *checkupval (lua_State *L, int argf, int argnup, int *pnup) {
  void *id;
  int nup = (int)luaL_checkinteger(L, argnup);
  luaL_checktype(L, argf, 6);
  id = lua_upvalueid(L, argf, nup);
  if (pnup) {
    ((void)((id != ((void*)0)) || luaL_argerror(L, (argnup), ("invalid upvalue index"))));
    *pnup = nup;
  }
  return id;
}
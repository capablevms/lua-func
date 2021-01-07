
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
extern void lua_pushlightuserdata(lua_State *, void *);
extern void * checkupval(lua_State *, int, int, int *);

static int db_upvalueid (lua_State *L) {
  void *id = checkupval(L, 1, 2, ((void*)0));
  if (id != ((void*)0))
    lua_pushlightuserdata(L, id);
  else
    lua_pushnil(L);
  return 1;
}
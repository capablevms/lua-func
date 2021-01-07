
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



extern void lua_setwarnf(lua_State *, lua_WarnFunction, void *);
extern int luaL_ref(lua_State *, int);
extern void * lua_newuserdatauv(lua_State *, size_t, int);
extern lua_CFunction lua_atpanic(lua_State *, lua_CFunction);
extern lua_State * lua_newstate(lua_Alloc, void *);

extern lua_State *luaL_newstate (void) {
  lua_State *L = lua_newstate(l_alloc, ((void*)0));
  if (L) {
    int *warnstate;
    lua_atpanic(L, &panic);
    warnstate = (int *)lua_newuserdatauv(L, sizeof(int), 0);
    luaL_ref(L, (-1000000 - 1000));
    *warnstate = 0;
    lua_setwarnf(L, warnf, warnstate);
  }
  return L;
}
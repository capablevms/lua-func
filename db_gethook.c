
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
extern int lua_gethookcount(lua_State *);
extern const char * lua_pushstring(lua_State *, const char *);
extern char * unmakemask(int, char *);
extern void lua_settop(lua_State *, int);
extern void lua_rotate(lua_State *, int, int);
extern int lua_rawget(lua_State *, int);
extern void lua_xmove(lua_State *, lua_State *, int);
extern int lua_pushthread(lua_State *);
extern void checkstack(lua_State *, lua_State *, int);
extern int lua_getfield(lua_State *, int, const char *);
extern const char * lua_pushstring(lua_State *, const char *);
extern void lua_pushnil(lua_State *);
extern lua_Hook lua_gethook(lua_State *);
extern int lua_gethookmask(lua_State *);
extern lua_State * getthread(lua_State *, int *);

static int db_gethook (lua_State *L) {
  int arg;
  lua_State *L1 = getthread(L, &arg);
  char buff[5];
  int mask = lua_gethookmask(L1);
  lua_Hook hook = lua_gethook(L1);
  if (hook == ((void*)0)) {
    lua_pushnil(L);
    return 1;
  }
  else if (hook != hookf)
    lua_pushstring(L, "" "external hook");
  else {
    lua_getfield(L, (-1000000 - 1000), HOOKKEY);
    checkstack(L, L1, 1);
    lua_pushthread(L1); lua_xmove(L1, L, 1);
    lua_rawget(L, -2);
    (lua_rotate(L, (-2), -1), lua_settop(L, -(1)-1));
  }
  lua_pushstring(L, unmakemask(mask, buff));
  lua_pushinteger(L, lua_gethookcount(L1));
  return 3;
}
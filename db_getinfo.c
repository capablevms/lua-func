
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



extern void treatstackoption(lua_State *, lua_State *, const char *);
extern char * strchr(const char *, int);
extern void treatstackoption(lua_State *, lua_State *, const char *);
extern char * strchr(const char *, int);
extern void settabsb(lua_State *, const char *, int);
extern char * strchr(const char *, int);
extern void settabsi(lua_State *, const char *, int);
extern void settabsi(lua_State *, const char *, int);
extern char * strchr(const char *, int);
extern void settabss(lua_State *, const char *, const char *);
extern void settabss(lua_State *, const char *, const char *);
extern char * strchr(const char *, int);
extern void settabsb(lua_State *, const char *, int);
extern void settabsi(lua_State *, const char *, int);
extern void settabsi(lua_State *, const char *, int);
extern char * strchr(const char *, int);
extern void settabsi(lua_State *, const char *, int);
extern char * strchr(const char *, int);
extern void settabss(lua_State *, const char *, const char *);
extern void settabsi(lua_State *, const char *, int);
extern void settabsi(lua_State *, const char *, int);
extern void settabss(lua_State *, const char *, const char *);
extern void lua_setfield(lua_State *, int, const char *);
extern const char * lua_pushlstring(lua_State *, const char *, size_t);
extern char * strchr(const char *, int);
extern void lua_createtable(lua_State *, int, int);
extern int luaL_argerror(lua_State *, int, const char *);
extern int lua_getinfo(lua_State *, const char *, lua_Debug *);
extern void lua_pushnil(lua_State *);
extern int lua_getstack(lua_State *, int, lua_Debug *);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern void lua_xmove(lua_State *, lua_State *, int);
extern void lua_pushvalue(lua_State *, int);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern int lua_type(lua_State *, int);
extern void checkstack(lua_State *, lua_State *, int);
extern const char * luaL_optlstring(lua_State *, int, const char *, size_t *);
extern lua_State * getthread(lua_State *, int *);

static int db_getinfo (lua_State *L) {
  lua_Debug ar;
  int arg;
  lua_State *L1 = getthread(L, &arg);
  const char *options = (luaL_optlstring(L, (arg+2), ("flnSrtu"), ((void*)0)));
  checkstack(L, L1, 3);
  if ((lua_type(L, (arg + 1)) == 6)) {
    options = lua_pushfstring(L, ">%s", options);
    lua_pushvalue(L, arg + 1);
    lua_xmove(L, L1, 1);
  }
  else {
    if (!lua_getstack(L1, (int)luaL_checkinteger(L, arg + 1), &ar)) {
      lua_pushnil(L);
      return 1;
    }
  }
  if (!lua_getinfo(L1, options, &ar))
    return luaL_argerror(L, arg+2, "invalid option");
  lua_createtable(L, 0, 0);
  if (strchr(options, 'S')) {
    lua_pushlstring(L, ar.source, ar.srclen);
    lua_setfield(L, -2, "source");
    settabss(L, "short_src", ar.short_src);
    settabsi(L, "linedefined", ar.linedefined);
    settabsi(L, "lastlinedefined", ar.lastlinedefined);
    settabss(L, "what", ar.what);
  }
  if (strchr(options, 'l'))
    settabsi(L, "currentline", ar.currentline);
  if (strchr(options, 'u')) {
    settabsi(L, "nups", ar.nups);
    settabsi(L, "nparams", ar.nparams);
    settabsb(L, "isvararg", ar.isvararg);
  }
  if (strchr(options, 'n')) {
    settabss(L, "name", ar.name);
    settabss(L, "namewhat", ar.namewhat);
  }
  if (strchr(options, 'r')) {
    settabsi(L, "ftransfer", ar.ftransfer);
    settabsi(L, "ntransfer", ar.ntransfer);
  }
  if (strchr(options, 't'))
    settabsb(L, "istailcall", ar.istailcall);
  if (strchr(options, 'L'))
    treatstackoption(L, L1, "activelines");
  if (strchr(options, 'f'))
    treatstackoption(L, L1, "func");
  return 1;
}
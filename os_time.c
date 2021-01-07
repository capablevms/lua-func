
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
extern int luaL_error(lua_State *, const char *, ...);
extern void setallfields(lua_State *, struct tm *);
extern time_t mktime(struct tm *);
extern int getboolfield(lua_State *, const char *);
extern int getfield(lua_State *, const char *, int, int);
extern int getfield(lua_State *, const char *, int, int);
extern int getfield(lua_State *, const char *, int, int);
extern int getfield(lua_State *, const char *, int, int);
extern int getfield(lua_State *, const char *, int, int);
extern int getfield(lua_State *, const char *, int, int);
extern void lua_settop(lua_State *, int);
extern void luaL_checktype(lua_State *, int, int);
extern time_t time(time_t *);
extern int lua_type(lua_State *, int);

static int os_time (lua_State *L) {
  time_t t;
  if ((lua_type(L, (1)) <= 0))
    t = time(((void*)0));
  else {
    struct tm ts;
    luaL_checktype(L, 1, 5);
    lua_settop(L, 1);
    ts.tm_year = getfield(L, "year", -1, 1900);
    ts.tm_mon = getfield(L, "month", -1, 1);
    ts.tm_mday = getfield(L, "day", -1, 0);
    ts.tm_hour = getfield(L, "hour", 12, 0);
    ts.tm_min = getfield(L, "min", 0, 0);
    ts.tm_sec = getfield(L, "sec", 0, 0);
    ts.tm_isdst = getboolfield(L, "isdst");
    t = mktime(&ts);
    setallfields(L, &ts);
  }
  if (t != (time_t)(lua_Integer)t || t == (time_t)(-1))
    return luaL_error(L,
                  "time result cannot be represented in this installation");
  lua_pushinteger(L,(lua_Integer)(t));
  return 1;
}
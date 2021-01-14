
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



extern int lookforfunc(lua_State *, const char *, const char *);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern int lookforfunc(lua_State *, const char *, const char *);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern const char * lua_pushlstring(lua_State *, const char *, size_t);
extern char * strchr(const char *, int);
extern const char * luaL_gsub(lua_State *, const char *, const char *, const char *);

extern int loadfunc (lua_State *L, const char *filename, const char *modname) {
  const char *openfunc;
  const char *mark;
  modname = luaL_gsub(L, modname, ".", "_");
  mark = strchr(modname, *"-");
  if (mark) {
    int stat;
    openfunc = lua_pushlstring(L, modname, mark - modname);
    openfunc = lua_pushfstring(L, "luaopen_""%s", openfunc);
    stat = lookforfunc(L, filename, openfunc);
    if (stat != 2) return stat;
    modname = mark + 1;
  }
  openfunc = lua_pushfstring(L, "luaopen_""%s", modname);
  return lookforfunc(L, filename, openfunc);
}
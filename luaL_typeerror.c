
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
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern const char * lua_typename(lua_State *, int);
extern int lua_type(lua_State *, int);
extern int lua_type(lua_State *, int);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern int luaL_getmetafield(lua_State *, int, const char *);

int luaL_typeerror (lua_State *L, int arg, const char *tname) {
  const char *msg;
  const char *typearg;
  if (luaL_getmetafield(L, arg, "__name") == 4)
    typearg = lua_tolstring(L, (-1), ((void*)0));
  else if (lua_type(L, arg) == 2)
    typearg = "light userdata";
  else
    typearg = lua_typename(L, lua_type(L,(arg)));
  msg = lua_pushfstring(L, "%s expected, got %s", tname, typearg);
  return luaL_argerror(L, arg, msg);
}
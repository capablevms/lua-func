
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



extern void luaL_traceback(lua_State *, lua_State *, const char *, int);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern const char * lua_typename(lua_State *, int);
extern int lua_type(lua_State *, int);
extern int lua_type(lua_State *, int);
extern int luaL_callmeta(lua_State *, int, const char *);
extern const char * lua_tolstring(lua_State *, int, size_t *);

static int msghandler (lua_State *L) {
  const char *msg = lua_tolstring(L, (1), ((void*)0));
  if (msg == ((void*)0)) {
    if (luaL_callmeta(L, 1, "__tostring") &&
        lua_type(L, -1) == 4)
      return 1;
    else
      msg = lua_pushfstring(L, "(error object is a %s value)",
                               lua_typename(L, lua_type(L,(1))));
  }
  luaL_traceback(L, L, msg, 1);
  return 1;
}
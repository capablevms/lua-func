
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



extern void lua_callk(lua_State *, int, int, lua_KContext, lua_KFunction);
extern void lua_rotate(lua_State *, int, int);
extern int luaL_error(lua_State *, const char *, ...);
extern const char * lua_typename(lua_State *, int);
extern int lua_type(lua_State *, int);
extern const char * lua_typename(lua_State *, int);
extern int lua_type(lua_State *, int);
extern int luaL_getmetafield(lua_State *, int, const char *);
extern int lua_type(lua_State *, int);
extern void lua_settop(lua_State *, int);

static void trymt (lua_State *L, const char *mtname) {
  lua_settop(L, 2);
  if (lua_type(L, 2) == 4 || !luaL_getmetafield(L, 2, mtname))
    luaL_error(L, "attempt to %s a '%s' with a '%s'", mtname + 2,
                  lua_typename(L, lua_type(L,(-2))), lua_typename(L, lua_type(L,(-1))));
  lua_rotate(L, (-3), 1);
  lua_callk(L, (2), (1), 0, ((void*)0));
}
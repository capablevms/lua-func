
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

extern const char *const HOOKKEY;

extern void lua_callk(lua_State *, int, int, lua_KContext, lua_KFunction);
extern void lua_pushnil(lua_State *);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern const char * lua_pushstring(lua_State *, const char *);
extern int lua_rawget(lua_State *, int);
extern int lua_pushthread(lua_State *);
extern int lua_getfield(lua_State *, int, const char *);

static void hookf (lua_State *L, lua_Debug *ar) {
  static const char *const hooknames[] =
    {"call", "return", "line", "count", "tail call"};
  lua_getfield(L, (-1000000 - 1000), HOOKKEY);
  lua_pushthread(L);
  if (lua_rawget(L, -2) == 6) {
    lua_pushstring(L, hooknames[(int)ar->event]);
    if (ar->currentline >= 0)
      lua_pushinteger(L, ar->currentline);
    else lua_pushnil(L);
    ((void)0);
    lua_callk(L, (2), (0), 0, ((void*)0));
  }
}
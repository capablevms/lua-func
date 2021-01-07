
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



extern const char * lua_pushstring(lua_State *, const char *);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern const char * lua_pushstring(lua_State *, const char *);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern void lua_settop(lua_State *, int);
extern void lua_rotate(lua_State *, int, int);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern int pushglobalfuncname(lua_State *, lua_Debug *);

static void pushfuncname (lua_State *L, lua_Debug *ar) {
  if (pushglobalfuncname(L, ar)) {
    lua_pushfstring(L, "function '%s'", lua_tolstring(L, (-1), ((void*)0)));
    (lua_rotate(L, (-2), -1), lua_settop(L, -(1)-1));
  }
  else if (*ar->namewhat != '\0')
    lua_pushfstring(L, "%s '%s'", ar->namewhat, ar->name);
  else if (*ar->what == 'm')
      lua_pushstring(L, "" "main chunk");
  else if (*ar->what != 'C')
    lua_pushfstring(L, "function <%s:%d>", ar->short_src, ar->linedefined);
  else
    lua_pushstring(L, "" "?");
}
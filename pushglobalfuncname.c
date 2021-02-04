
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



extern void lua_settop(lua_State *, int);
extern void lua_settop(lua_State *, int);
extern void lua_copy(lua_State *, int, int);
extern void lua_settop(lua_State *, int);
extern void lua_rotate(lua_State *, int, int);
extern const char * lua_pushstring(lua_State *, const char *);
extern int strncmp(const char *, const char *, size_t);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern int findfield(lua_State *, int, int);
extern int lua_getfield(lua_State *, int, const char *);
extern int lua_getinfo(lua_State *, const char *, lua_Debug *);
extern int lua_gettop(lua_State *);

extern int pushglobalfuncname (lua_State *L, lua_Debug *ar) {
  int top = lua_gettop(L);
  lua_getinfo(L, "f", ar);
  lua_getfield(L, (-1000000 - 1000), "_LOADED");
  if (findfield(L, top + 1, 2)) {
    const char *name = lua_tolstring(L, (-1), ((void*)0));
    if (strncmp(name, "_G" ".", 3) == 0) {
      lua_pushstring(L, name + 3);
      (lua_rotate(L, (-2), -1), lua_settop(L, -(1)-1));
    }
    lua_copy(L, -1, top + 1);
    lua_settop(L, top + 1);
    return 1;
  }
  else {
    lua_settop(L, top);
    return 0;
  }
}
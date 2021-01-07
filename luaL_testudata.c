
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
extern int lua_rawequal(lua_State *, int, int);
extern int lua_getfield(lua_State *, int, const char *);
extern int lua_getmetatable(lua_State *, int);
extern void * lua_touserdata(lua_State *, int);

extern void *luaL_testudata (lua_State *L, int ud, const char *tname) {
  void *p = lua_touserdata(L, ud);
  if (p != ((void*)0)) {
    if (lua_getmetatable(L, ud)) {
      (lua_getfield(L, (-1000000 - 1000), (tname)));
      if (!lua_rawequal(L, -1, -2))
        p = ((void*)0);
      lua_settop(L, -(2)-1);
      return p;
    }
  }
  return ((void*)0);
}
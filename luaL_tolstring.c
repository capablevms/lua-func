
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



extern const char * lua_tolstring(lua_State *, int, size_t *);
extern void lua_settop(lua_State *, int);
extern void lua_rotate(lua_State *, int, int);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern const void * lua_topointer(lua_State *, int);
extern const char * lua_typename(lua_State *, int);
extern int lua_type(lua_State *, int);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern int luaL_getmetafield(lua_State *, int, const char *);
extern const char * lua_pushstring(lua_State *, const char *);
extern const char * lua_pushstring(lua_State *, const char *);
extern int lua_toboolean(lua_State *, int);
extern void lua_pushvalue(lua_State *, int);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern lua_Number lua_tonumberx(lua_State *, int, int *);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern lua_Integer lua_tointegerx(lua_State *, int, int *);
extern int lua_isinteger(lua_State *, int);
extern int lua_type(lua_State *, int);
extern int luaL_error(lua_State *, const char *, ...);
extern int lua_isstring(lua_State *, int);
extern int luaL_callmeta(lua_State *, int, const char *);

extern const char *luaL_tolstring (lua_State *L, int idx, size_t *len) {
  if (luaL_callmeta(L, idx, "__tostring")) {
    if (!lua_isstring(L, -1))
      luaL_error(L, "'__tostring' must return a string");
  }
  else {
    switch (lua_type(L, idx)) {
      case 3: {
        if (lua_isinteger(L, idx))
          lua_pushfstring(L, "%I", (long long)lua_tointegerx(L,(idx),((void*)0)));
        else
          lua_pushfstring(L, "%f", (double)lua_tonumberx(L,(idx),((void*)0)));
        break;
      }
      case 4:
        lua_pushvalue(L, idx);
        break;
      case 1:
        lua_pushstring(L, (lua_toboolean(L, idx) ? "true" : "false"));
        break;
      case 0:
        lua_pushstring(L, "" "nil");
        break;
      default: {
        int tt = luaL_getmetafield(L, idx, "__name");
        const char *kind = (tt == 4) ? lua_tolstring(L, (-1), ((void*)0)) :
                                                 lua_typename(L, lua_type(L,(idx)));
        lua_pushfstring(L, "%s: %p", kind, lua_topointer(L, idx));
        if (tt != 0)
          (lua_rotate(L, (-2), -1), lua_settop(L, -(1)-1));
        break;
      }
    }
  }
  return lua_tolstring(L, -1, len);
}

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

typedef luaL_Stream LStream;


extern int aux_close(lua_State *);
extern void lua_pushvalue(lua_State *, int);
extern void lua_settop(lua_State *, int);
extern int lua_toboolean(lua_State *, int);
extern int luaL_error(lua_State *, const char *, ...);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern int lua_toboolean(lua_State *, int);
extern int g_read(lua_State *, FILE *, int);
extern void lua_pushvalue(lua_State *, int);
extern void luaL_checkstack(lua_State *, int, const char *);
extern void lua_settop(lua_State *, int);
extern int luaL_error(lua_State *, const char *, ...);
extern lua_Integer lua_tointegerx(lua_State *, int, int *);
extern void * lua_touserdata(lua_State *, int);

extern int io_readline (lua_State *L) {
  LStream *p = (LStream *)lua_touserdata(L, ((-1000000 - 1000) - (1)));
  int i;
  int n = (int)lua_tointegerx(L,(((-1000000 - 1000) - (2))),((void*)0));
  if (((p)->closef == ((void*)0)))
    return luaL_error(L, "file is already closed");
  lua_settop(L , 1);
  luaL_checkstack(L, n, "too many arguments");
  for (i = 1; i <= n; i++)
    lua_pushvalue(L, ((-1000000 - 1000) - (3 + i)));
  n = g_read(L, p->f, 2);
  ((void)0);
  if (lua_toboolean(L, -n))
    return n;
  else {
    if (n > 1) {

      return luaL_error(L, "%s", lua_tolstring(L, (-n + 1), ((void*)0)));
    }
    if (lua_toboolean(L, ((-1000000 - 1000) - (3)))) {
      lua_settop(L, 0);
      lua_pushvalue(L, ((-1000000 - 1000) - (1)));
      aux_close(L);
    }
    return 0;
  }
}
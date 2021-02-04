
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



extern void lua_warning(lua_State *, const char *, int);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern void lua_warning(lua_State *, const char *, int);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern int lua_gettop(lua_State *);

extern int luaB_warn (lua_State *L) {
  int n = lua_gettop(L);
  int i;
  (luaL_checklstring(L, (1), ((void*)0)));
  for (i = 2; i <= n; i++)
    (luaL_checklstring(L, (i), ((void*)0)));
  for (i = 1; i < n; i++)
    lua_warning(L, lua_tolstring(L, (i), ((void*)0)), 1);
  lua_warning(L, lua_tolstring(L, (n), ((void*)0)), 0);
  return 0;
}
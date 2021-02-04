
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
extern void lua_rotate(lua_State *, int, int);
extern void lua_pushnil(lua_State *);
extern int lookforfunc(lua_State *, const char *, const char *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

extern int ll_loadlib (lua_State *L) {
  const char *path = (luaL_checklstring(L, (1), ((void*)0)));
  const char *init = (luaL_checklstring(L, (2), ((void*)0)));
  int stat = lookforfunc(L, path, init);
  if (stat == 0)
    return 1;
  else {
    lua_pushnil(L);
    lua_rotate(L, (-2), 1);
    lua_pushstring(L, (stat == 1) ? "absent" : "init");
    return 3;
  }
}

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



extern void lua_rotate(lua_State *, int, int);
extern void lua_pushnil(lua_State *);
extern const char * searchpath(lua_State *, const char *, const char *, const char *, const char *);
extern const char * luaL_optlstring(lua_State *, int, const char *, size_t *);
extern const char * luaL_optlstring(lua_State *, int, const char *, size_t *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

static int ll_searchpath (lua_State *L) {
  const char *f = searchpath(L, (luaL_checklstring(L, (1), ((void*)0))),
                                (luaL_checklstring(L, (2), ((void*)0))),
                                (luaL_optlstring(L, (3), ("."), ((void*)0))),
                                (luaL_optlstring(L, (4), ("/"), ((void*)0))));
  if (f != ((void*)0)) return 1;
  else {
    lua_pushnil(L);
    lua_rotate(L, (-2), 1);
    return 2;
  }
}
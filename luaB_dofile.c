
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



extern int dofilecont(lua_State *, int, lua_KContext);
extern void lua_callk(lua_State *, int, int, lua_KContext, lua_KFunction);
extern int lua_error(lua_State *);
extern int luaL_loadfilex(lua_State *, const char *, const char *);
extern void lua_settop(lua_State *, int);
extern const char * luaL_optlstring(lua_State *, int, const char *, size_t *);

extern int luaB_dofile (lua_State *L) {
  const char *fname = (luaL_optlstring(L, (1), (((void*)0)), ((void*)0)));
  lua_settop(L, 1);
  if (luaL_loadfilex(L,fname,((void*)0)) != 0)
    return lua_error(L);
  lua_callk(L, 0, (-1), 0, dofilecont);
  return dofilecont(L, 0, 0);
}
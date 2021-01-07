
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



extern int load_aux(lua_State *, int, int);
extern int luaL_loadfilex(lua_State *, const char *, const char *);
extern int lua_type(lua_State *, int);
extern const char * luaL_optlstring(lua_State *, int, const char *, size_t *);
extern const char * luaL_optlstring(lua_State *, int, const char *, size_t *);

static int luaB_loadfile (lua_State *L) {
  const char *fname = (luaL_optlstring(L, (1), (((void*)0)), ((void*)0)));
  const char *mode = (luaL_optlstring(L, (2), (((void*)0)), ((void*)0)));
  int env = (!(lua_type(L, (3)) == (-1)) ? 3 : 0);
  int status = luaL_loadfilex(L, fname, mode);
  return load_aux(L, status, env);
}
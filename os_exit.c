
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



extern void exit(int);
extern void lua_close(lua_State *);
extern int lua_toboolean(lua_State *, int);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern int lua_toboolean(lua_State *, int);
extern int lua_type(lua_State *, int);

extern int os_exit (lua_State *L) {
  int status;
  if ((lua_type(L, (1)) == 1))
    status = (lua_toboolean(L, 1) ? 0 : 1);
  else
    status = (int)luaL_optinteger(L, 1, 0);
  if (lua_toboolean(L, 2))
    lua_close(L);
  if (L) exit(status);
  return 0;
}
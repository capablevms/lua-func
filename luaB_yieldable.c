
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



extern void lua_pushboolean(lua_State *, int);
extern int lua_isyieldable(lua_State *);
extern lua_State * getco(lua_State *);
extern int lua_type(lua_State *, int);

static int luaB_yieldable (lua_State *L) {
  lua_State *co = (lua_type(L, (1)) == (-1)) ? L : getco(L);
  lua_pushboolean(L, lua_isyieldable(co));
  return 1;
}
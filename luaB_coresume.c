
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
extern void lua_pushboolean(lua_State *, int);
extern void lua_rotate(lua_State *, int, int);
extern void lua_pushboolean(lua_State *, int);
extern int auxresume(lua_State *, lua_State *, int);
extern int lua_gettop(lua_State *);
extern lua_State * getco(lua_State *);

extern int luaB_coresume (lua_State *L) {
  lua_State *co = getco(L);
  int r;
  r = auxresume(L, co, lua_gettop(L) - 1);
  if (r < 0) {
    lua_pushboolean(L, 0);
    lua_rotate(L, (-2), 1);
    return 2;
  }
  else {
    lua_pushboolean(L, 1);
    lua_rotate(L, (-(r + 1)), 1);
    return r + 1;
  }
}
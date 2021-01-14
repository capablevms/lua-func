
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

extern const char *const statname[];

extern int luaL_error(lua_State *, const char *, ...);
extern void lua_xmove(lua_State *, lua_State *, int);
extern void lua_pushboolean(lua_State *, int);
extern void lua_pushboolean(lua_State *, int);
extern int lua_resetthread(lua_State *);
extern int auxstatus(lua_State *, lua_State *);
extern lua_State * getco(lua_State *);

extern int luaB_close (lua_State *L) {
  lua_State *co = getco(L);
  int status = auxstatus(L, co);
  switch (status) {
    case 1: case 2: {
      status = lua_resetthread(co);
      if (status == 0) {
        lua_pushboolean(L, 1);
        return 1;
      }
      else {
        lua_pushboolean(L, 0);
        lua_xmove(co, L, 1);
        return 2;
      }
    }
    default:
      return luaL_error(L, "cannot close a %s coroutine", statname[status]);
  }
}
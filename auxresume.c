
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



extern void lua_xmove(lua_State *, lua_State *, int);
extern void lua_xmove(lua_State *, lua_State *, int);
extern const char * lua_pushstring(lua_State *, const char *);
extern void lua_settop(lua_State *, int);
extern int lua_checkstack(lua_State *, int);
extern int lua_resume(lua_State *, lua_State *, int, int *);
extern void lua_xmove(lua_State *, lua_State *, int);
extern const char * lua_pushstring(lua_State *, const char *);
extern int lua_checkstack(lua_State *, int);

static int auxresume (lua_State *L, lua_State *co, int narg) {
  int status, nres;
  if (!lua_checkstack(co, narg)) {
    lua_pushstring(L, "" "too many arguments to resume");
    return -1;
  }
  lua_xmove(L, co, narg);
  status = lua_resume(co, L, narg, &nres);
  if (status == 0 || status == 1) {
    if (!lua_checkstack(L, nres + 1)) {
      lua_settop(co, -(nres)-1);
      lua_pushstring(L, "" "too many results to resume");
      return -1;
    }
    lua_xmove(co, L, nres);
    return nres;
  }
  else {
    lua_xmove(co, L, 1);
    return -1;
  }
}
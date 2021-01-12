
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

extern const char *progname;

extern void l_message(const char *, const char *);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern int lua_pcallk(lua_State *, int, int, int, lua_KContext, lua_KFunction);
extern void lua_rotate(lua_State *, int, int);
extern int lua_getglobal(lua_State *, const char *);
extern void luaL_checkstack(lua_State *, int, const char *);
extern int lua_gettop(lua_State *);

static void l_print (lua_State *L) {
  int n = lua_gettop(L);
  if (n > 0) {
    luaL_checkstack(L, 20, "too many results to print");
    lua_getglobal(L, "print");
    lua_rotate(L, (1), 1);
    if (lua_pcallk(L, (n), (0), (0), 0, ((void*)0)) != 0)
      l_message(progname, lua_pushfstring(L, "error calling 'print' (%s)",
                                             lua_tolstring(L, (-1), ((void*)0))));
  }
}
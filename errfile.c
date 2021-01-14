
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



extern void lua_settop(lua_State *, int);
extern void lua_rotate(lua_State *, int, int);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern char * strerror(int);
extern int * __errno_location();

extern int errfile (lua_State *L, const char *what, int fnameindex) {
  const char *serr = strerror((*__errno_location ()));
  const char *filename = lua_tolstring(L, (fnameindex), ((void*)0)) + 1;
  lua_pushfstring(L, "cannot %s %s: %s", what, filename, serr);
  (lua_rotate(L, (fnameindex), -1), lua_settop(L, -(1)-1));
  return (5 +1);
}
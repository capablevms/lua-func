
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



extern void luaD_throw(lua_State *, int);
extern const char * luaO_pushfstring(lua_State *, const char *, ...);
extern char * strchr(const char *, int);

extern void checkmode (lua_State *L, const char *mode, const char *x) {
  if (mode && strchr(mode, x[0]) == ((void*)0)) {
    luaO_pushfstring(L,
       "attempt to load a %s chunk (mode is '%s')", x, mode);
    luaD_throw(L, 3);
  }
}
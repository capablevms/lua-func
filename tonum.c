
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



extern size_t lua_stringtonumber(lua_State *, const char *);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern void lua_pushvalue(lua_State *, int);
extern int lua_type(lua_State *, int);

extern int tonum (lua_State *L, int arg) {
  if (lua_type(L, arg) == 3) {
    lua_pushvalue(L, arg);
    return 1;
  }
  else {
    size_t len;
    const char *s = lua_tolstring(L, arg, &len);
    return (s != ((void*)0) && lua_stringtonumber(L, s) == len + 1);
  }
}
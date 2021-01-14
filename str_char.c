
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



extern void luaL_pushresultsize(luaL_Buffer *, size_t);
extern int luaL_argerror(lua_State *, int, const char *);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern char * luaL_buffinitsize(lua_State *, luaL_Buffer *, size_t);
extern int lua_gettop(lua_State *);

extern int str_char (lua_State *L) {
  int n = lua_gettop(L);
  int i;
  luaL_Buffer b;
  char *p = luaL_buffinitsize(L, &b, n);
  for (i=1; i<=n; i++) {
    lua_Unsigned c = (lua_Unsigned)luaL_checkinteger(L, i);
    ((void)((c <= (lua_Unsigned)(127*2 +1)) || luaL_argerror(L, (i), ("value out of range"))));
    p[i - 1] = ((unsigned char)(c));
  }
  luaL_pushresultsize(&b, n);
  return 1;
}
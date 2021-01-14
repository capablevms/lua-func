
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
extern const char * lua_pushstring(lua_State *, const char *);
extern const char * lua_setupvalue(lua_State *, int, int);
extern const char * lua_getupvalue(lua_State *, int, int);
extern void luaL_checktype(lua_State *, int, int);
extern lua_Integer luaL_checkinteger(lua_State *, int);

extern int auxupvalue (lua_State *L, int get) {
  const char *name;
  int n = (int)luaL_checkinteger(L, 2);
  luaL_checktype(L, 1, 6);
  name = get ? lua_getupvalue(L, 1, n) : lua_setupvalue(L, 1, n);
  if (name == ((void*)0)) return 0;
  lua_pushstring(L, name);
  lua_rotate(L, (-(get+1)), 1);
  return get + 1;
}
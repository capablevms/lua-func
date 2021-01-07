
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

typedef struct {
  unsigned long s[4];
} RanState;


extern void setrandfunc(lua_State *);
extern void lua_setfield(lua_State *, int, const char *);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern void lua_setfield(lua_State *, int, const char *);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern void lua_setfield(lua_State *, int, const char *);
extern void lua_pushnumber(lua_State *, lua_Number);
extern double __builtin_huge_val();
extern void lua_setfield(lua_State *, int, const char *);
extern void lua_pushnumber(lua_State *, lua_Number);
extern void luaL_setfuncs(lua_State *, const luaL_Reg *, int);
extern void lua_createtable(lua_State *, int, int);
extern void luaL_checkversion_(lua_State *, lua_Number, size_t);

extern int luaopen_math (lua_State *L) {
  (luaL_checkversion_(L, 504, (sizeof(lua_Integer)*16 + sizeof(lua_Number))), lua_createtable(L, 0, sizeof(mathlib)/sizeof((mathlib)[0]) - 1), luaL_setfuncs(L,mathlib,0));
  lua_pushnumber(L, (3.141592653589793238462643383279502884));
  lua_setfield(L, -2, "pi");
  lua_pushnumber(L, (lua_Number)(__builtin_huge_val ()));
  lua_setfield(L, -2, "huge");
  lua_pushinteger(L, 9223372036854775807LL);
  lua_setfield(L, -2, "maxinteger");
  lua_pushinteger(L, (-9223372036854775807LL -1LL));
  lua_setfield(L, -2, "mininteger");
  setrandfunc(L);
  return 1;
}
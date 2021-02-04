
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

extern int math_type(lua_State *);
extern int math_tan(lua_State *);
extern int math_sqrt(lua_State *);
extern int math_sin(lua_State *);
extern int math_rad(lua_State *);
extern int math_modf(lua_State *);
extern int math_min(lua_State *);
extern int math_max(lua_State *);
extern int math_log(lua_State *);
extern int math_ult(lua_State *);
extern int math_fmod(lua_State *);
extern int math_floor(lua_State *);
extern int math_toint(lua_State *);
extern int math_exp(lua_State *);
extern int math_deg(lua_State *);
extern int math_cos(lua_State *);
extern int math_ceil(lua_State *);
extern int math_atan(lua_State *);
extern int math_asin(lua_State *);
extern int math_acos(lua_State *);
extern int math_abs(lua_State *);

static const luaL_Reg mathlib[] = {
  {"abs", math_abs},
  {"acos", math_acos},
  {"asin", math_asin},
  {"atan", math_atan},
  {"ceil", math_ceil},
  {"cos", math_cos},
  {"deg", math_deg},
  {"exp", math_exp},
  {"tointeger", math_toint},
  {"floor", math_floor},
  {"fmod", math_fmod},
  {"ult", math_ult},
  {"log", math_log},
  {"max", math_max},
  {"min", math_min},
  {"modf", math_modf},
  {"rad", math_rad},
  {"sin", math_sin},
  {"sqrt", math_sqrt},
  {"tan", math_tan},
  {"type", math_type},
# 737 "lmathlib.c"
  {"random", ((void*)0)},
  {"randomseed", ((void*)0)},
  {"pi", ((void*)0)},
  {"huge", ((void*)0)},
  {"maxinteger", ((void*)0)},
  {"mininteger", ((void*)0)},
  {((void*)0), ((void*)0)}
};

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
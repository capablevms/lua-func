
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

extern int f_setvbuf(lua_State *);
extern int f_close(lua_State *);
extern int f_seek(lua_State *);
extern int f_flush(lua_State *);
extern int f_lines(lua_State *);
extern int f_write(lua_State *);
extern int f_read(lua_State *);

static const luaL_Reg meth[] = {
  {"read", f_read},
  {"write", f_write},
  {"lines", f_lines},
  {"flush", f_flush},
  {"seek", f_seek},
  {"close", f_close},
  {"setvbuf", f_setvbuf},
  {((void*)0), ((void*)0)}
};

extern int f_tostring(lua_State *);
extern int f_gc(lua_State *);
extern int f_gc(lua_State *);

static const luaL_Reg metameth[] = {
  {"__index", ((void*)0)},
  {"__gc", f_gc},
  {"__close", f_gc},
  {"__tostring", f_tostring},
  {((void*)0), ((void*)0)}
};

extern void lua_settop(lua_State *, int);
extern void lua_setfield(lua_State *, int, const char *);
extern void luaL_setfuncs(lua_State *, const luaL_Reg *, int);
extern void lua_createtable(lua_State *, int, int);
extern void luaL_setfuncs(lua_State *, const luaL_Reg *, int);
extern int luaL_newmetatable(lua_State *, const char *);

extern void createmeta (lua_State *L) {
  luaL_newmetatable(L, "FILE*");
  luaL_setfuncs(L, metameth, 0);
  lua_createtable(L, 0, sizeof(meth)/sizeof((meth)[0]) - 1);
  luaL_setfuncs(L, meth, 0);
  lua_setfield(L, -2, "__index");
  lua_settop(L, -(1)-1);
}
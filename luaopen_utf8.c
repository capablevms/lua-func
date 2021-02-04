
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

extern int iter_codes(lua_State *);
extern int utflen(lua_State *);
extern int utfchar(lua_State *);
extern int codepoint(lua_State *);
extern int byteoffset(lua_State *);

static const luaL_Reg funcs[] = {
  {"offset", byteoffset},
  {"codepoint", codepoint},
  {"char", utfchar},
  {"len", utflen},
  {"codes", iter_codes},

  {"charpattern", ((void*)0)},
  {((void*)0), ((void*)0)}
};

extern void lua_setfield(lua_State *, int, const char *);
extern const char * lua_pushlstring(lua_State *, const char *, size_t);
extern void luaL_setfuncs(lua_State *, const luaL_Reg *, int);
extern void lua_createtable(lua_State *, int, int);
extern void luaL_checkversion_(lua_State *, lua_Number, size_t);

extern int luaopen_utf8 (lua_State *L) {
  (luaL_checkversion_(L, 504, (sizeof(lua_Integer)*16 + sizeof(lua_Number))), lua_createtable(L, 0, sizeof(funcs)/sizeof((funcs)[0]) - 1), luaL_setfuncs(L,funcs,0));
  lua_pushlstring(L, "[\0-\x7F\xC2-\xFD][\x80-\xBF]*", sizeof("[\0-\x7F\xC2-\xFD][\x80-\xBF]*")/sizeof(char) - 1);
  lua_setfield(L, -2, "charpattern");
  return 1;
}
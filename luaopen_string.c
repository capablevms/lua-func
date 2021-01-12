
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

extern int str_unpack(lua_State *);
extern int str_packsize(lua_State *);
extern int str_pack(lua_State *);
extern int str_upper(lua_State *);
extern int str_sub(lua_State *);
extern int str_reverse(lua_State *);
extern int str_rep(lua_State *);
extern int str_match(lua_State *);
extern int str_lower(lua_State *);
extern int str_len(lua_State *);
extern int str_gsub(lua_State *);
extern int gmatch(lua_State *);
extern int str_format(lua_State *);
extern int str_find(lua_State *);
extern int str_dump(lua_State *);
extern int str_char(lua_State *);
extern int str_byte(lua_State *);

static const luaL_Reg strlib[] = {
  {"byte", str_byte},
  {"char", str_char},
  {"dump", str_dump},
  {"find", str_find},
  {"format", str_format},
  {"gmatch", gmatch},
  {"gsub", str_gsub},
  {"len", str_len},
  {"lower", str_lower},
  {"match", str_match},
  {"rep", str_rep},
  {"reverse", str_reverse},
  {"sub", str_sub},
  {"upper", str_upper},
  {"pack", str_pack},
  {"packsize", str_packsize},
  {"unpack", str_unpack},
  {((void*)0), ((void*)0)}
};

extern void createmetatable(lua_State *);
extern void luaL_setfuncs(lua_State *, const luaL_Reg *, int);
extern void lua_createtable(lua_State *, int, int);
extern void luaL_checkversion_(lua_State *, lua_Number, size_t);

extern int luaopen_string (lua_State *L) {
  (luaL_checkversion_(L, 504, (sizeof(lua_Integer)*16 + sizeof(lua_Number))), lua_createtable(L, 0, sizeof(strlib)/sizeof((strlib)[0]) - 1), luaL_setfuncs(L,strlib,0));
  createmetatable(L);
  return 1;
}
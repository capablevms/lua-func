
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

extern int luaB_xpcall(lua_State *);
extern int luaB_type(lua_State *);
extern int luaB_tostring(lua_State *);
extern int luaB_tonumber(lua_State *);
extern int luaB_setmetatable(lua_State *);
extern int luaB_select(lua_State *);
extern int luaB_rawset(lua_State *);
extern int luaB_rawget(lua_State *);
extern int luaB_rawlen(lua_State *);
extern int luaB_rawequal(lua_State *);
extern int luaB_warn(lua_State *);
extern int luaB_print(lua_State *);
extern int luaB_pcall(lua_State *);
extern int luaB_pairs(lua_State *);
extern int luaB_next(lua_State *);
extern int luaB_load(lua_State *);
extern int luaB_loadfile(lua_State *);
extern int luaB_ipairs(lua_State *);
extern int luaB_getmetatable(lua_State *);
extern int luaB_error(lua_State *);
extern int luaB_dofile(lua_State *);
extern int luaB_collectgarbage(lua_State *);
extern int luaB_assert(lua_State *);

static const luaL_Reg base_funcs[] = {
  {"assert", luaB_assert},
  {"collectgarbage", luaB_collectgarbage},
  {"dofile", luaB_dofile},
  {"error", luaB_error},
  {"getmetatable", luaB_getmetatable},
  {"ipairs", luaB_ipairs},
  {"loadfile", luaB_loadfile},
  {"load", luaB_load},
  {"next", luaB_next},
  {"pairs", luaB_pairs},
  {"pcall", luaB_pcall},
  {"print", luaB_print},
  {"warn", luaB_warn},
  {"rawequal", luaB_rawequal},
  {"rawlen", luaB_rawlen},
  {"rawget", luaB_rawget},
  {"rawset", luaB_rawset},
  {"select", luaB_select},
  {"setmetatable", luaB_setmetatable},
  {"tonumber", luaB_tonumber},
  {"tostring", luaB_tostring},
  {"type", luaB_type},
  {"xpcall", luaB_xpcall},

  {"_G", ((void*)0)},
  {"_VERSION", ((void*)0)},
  {((void*)0), ((void*)0)}
};

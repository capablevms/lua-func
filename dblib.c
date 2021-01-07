
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

extern int db_setcstacklimit(lua_State *);
extern int db_traceback(lua_State *);
extern int db_setupvalue(lua_State *);
extern int db_setmetatable(lua_State *);
extern int db_setlocal(lua_State *);
extern int db_sethook(lua_State *);
extern int db_setuservalue(lua_State *);
extern int db_upvalueid(lua_State *);
extern int db_upvaluejoin(lua_State *);
extern int db_getupvalue(lua_State *);
extern int db_getmetatable(lua_State *);
extern int db_getregistry(lua_State *);
extern int db_getlocal(lua_State *);
extern int db_getinfo(lua_State *);
extern int db_gethook(lua_State *);
extern int db_getuservalue(lua_State *);
extern int db_debug(lua_State *);

static const luaL_Reg dblib[] = {
  {"debug", db_debug},
  {"getuservalue", db_getuservalue},
  {"gethook", db_gethook},
  {"getinfo", db_getinfo},
  {"getlocal", db_getlocal},
  {"getregistry", db_getregistry},
  {"getmetatable", db_getmetatable},
  {"getupvalue", db_getupvalue},
  {"upvaluejoin", db_upvaluejoin},
  {"upvalueid", db_upvalueid},
  {"setuservalue", db_setuservalue},
  {"sethook", db_sethook},
  {"setlocal", db_setlocal},
  {"setmetatable", db_setmetatable},
  {"setupvalue", db_setupvalue},
  {"traceback", db_traceback},
  {"setcstacklimit", db_setcstacklimit},
  {((void*)0), ((void*)0)}
};

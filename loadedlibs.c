
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

extern int luaopen_debug(lua_State *);
extern int luaopen_utf8(lua_State *);
extern int luaopen_math(lua_State *);
extern int luaopen_string(lua_State *);
extern int luaopen_os(lua_State *);
extern int luaopen_io(lua_State *);
extern int luaopen_table(lua_State *);
extern int luaopen_coroutine(lua_State *);
extern int luaopen_package(lua_State *);
extern int luaopen_base(lua_State *);

const luaL_Reg loadedlibs[] = {
  {"_G", luaopen_base},
  {"package", luaopen_package},
  {"coroutine", luaopen_coroutine},
  {"table", luaopen_table},
  {"io", luaopen_io},
  {"os", luaopen_os},
  {"string", luaopen_string},
  {"math", luaopen_math},
  {"utf8", luaopen_utf8},
  {"debug", luaopen_debug},
  {((void*)0), ((void*)0)}
};

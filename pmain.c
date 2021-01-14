
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

extern const char *progname;

extern void lua_pushboolean(lua_State *, int);
extern int dofile(lua_State *, const char *);
extern void doREPL(lua_State *);
extern void print_version();
extern void doREPL(lua_State *);
extern int handle_script(lua_State *, char **);
extern int runargs(lua_State *, char **, int);
extern int handle_luainit(lua_State *);
extern int lua_gc(lua_State *, int, ...);
extern void createargtable(lua_State *, char **, int, int);
extern void luaL_openlibs(lua_State *);
extern void lua_setfield(lua_State *, int, const char *);
extern void lua_pushboolean(lua_State *, int);
extern void print_version();
extern void print_usage(const char *);
extern void luaL_checkversion_(lua_State *, lua_Number, size_t);
extern int collectargs(char **, int *);
extern void * lua_touserdata(lua_State *, int);
extern lua_Integer lua_tointegerx(lua_State *, int, int *);

extern int pmain (lua_State *L) {
  int argc = (int)lua_tointegerx(L,(1),((void*)0));
  char **argv = (char **)lua_touserdata(L, 2);
  int script;
  int args = collectargs(argv, &script);
  luaL_checkversion_(L, 504, (sizeof(lua_Integer)*16 + sizeof(lua_Number)));
  if (argv[0] && argv[0][0]) progname = argv[0];
  if (args == 1) {
    print_usage(argv[script]);
    return 0;
  }
  if (args & 4)
    print_version();
  if (args & 16) {
    lua_pushboolean(L, 1);
    lua_setfield(L, (-1000000 - 1000), "LUA_NOENV");
  }
  luaL_openlibs(L);
  createargtable(L, argv, argc, script);
  lua_gc(L, 10, 0, 0);
  if (!(args & 16)) {
    if (handle_luainit(L) != 0)
      return 0;
  }
  if (!runargs(L, argv, script))
    return 0;
  if (script < argc &&
      handle_script(L, argv + script) != 0)
    return 0;
  if (args & 2)
    doREPL(L);
  else if (script == argc && !(args & (8 | 4))) {
    if (1) {
      print_version();
      doREPL(L);
    }
    else dofile(L, ((void*)0));
  }
  lua_pushboolean(L, 1);
  return 1;
}
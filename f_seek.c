
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

typedef luaL_Stream LStream;


extern void lua_pushinteger(lua_State *, lua_Integer);
extern long ftell(FILE *);
extern int luaL_fileresult(lua_State *, int, const char *);
extern int fseek(FILE *, long, int);
extern int luaL_argerror(lua_State *, int, const char *);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern int luaL_checkoption(lua_State *, int, const char *, const char *const *);
extern FILE * tofile(lua_State *);

extern int f_seek (lua_State *L) {
  static const int mode[] = {0, 1, 2};
  static const char *const modenames[] = {"set", "cur", "end", ((void*)0)};
  FILE *f = tofile(L);
  int op = luaL_checkoption(L, 2, "cur", modenames);
  lua_Integer p3 = luaL_optinteger(L, 3, 0);
  long offset = (long)p3;
  ((void)(((lua_Integer)offset == p3) || luaL_argerror(L, (3), ("not an integer in proper range"))));

  op = fseek(f,offset,mode[op]);
  if (op)
    return luaL_fileresult(L, 0, ((void*)0));
  else {
    lua_pushinteger(L, (lua_Integer)ftell(f));
    return 1;
  }
}
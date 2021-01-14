
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


extern int luaL_fileresult(lua_State *, int, const char *);
extern int setvbuf(FILE *restrict, char *restrict, int, size_t);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern int luaL_checkoption(lua_State *, int, const char *, const char *const *);
extern FILE * tofile(lua_State *);

extern int f_setvbuf (lua_State *L) {
  static const int mode[] = {2, 0, 1};
  static const char *const modenames[] = {"no", "full", "line", ((void*)0)};
  FILE *f = tofile(L);
  int op = luaL_checkoption(L, 2, ((void*)0), modenames);
  lua_Integer sz = luaL_optinteger(L, 3, ((int)(16 * sizeof(void*) * sizeof(lua_Number))));
  int res = setvbuf(f, ((void*)0), mode[op], (size_t)sz);
  return luaL_fileresult(L, res == 0, ((void*)0));
}
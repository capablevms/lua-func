
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



extern const char * lua_pushstring(lua_State *, const char *);
extern char * setlocale(int, const char *);
extern int luaL_checkoption(lua_State *, int, const char *, const char *const *);
extern const char * luaL_optlstring(lua_State *, int, const char *, size_t *);

extern int os_setlocale (lua_State *L) {
  static const int cat[] = {6, 3, 0, 4,
                      1, 2};
  static const char *const catnames[] = {"all", "collate", "ctype", "monetary",
     "numeric", "time", ((void*)0)};
  const char *l = (luaL_optlstring(L, (1), (((void*)0)), ((void*)0)));
  int op = luaL_checkoption(L, 2, "all", catnames);
  lua_pushstring(L, setlocale(cat[op], l));
  return 1;
}
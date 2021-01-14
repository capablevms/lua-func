
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



extern void lua_pushboolean(lua_State *, int);
extern int luaL_execresult(lua_State *, int);
extern int system(const char *);
extern int * __errno_location();
extern const char * luaL_optlstring(lua_State *, int, const char *, size_t *);

extern int os_execute (lua_State *L) {
  const char *cmd = (luaL_optlstring(L, (1), (((void*)0)), ((void*)0)));
  int stat;
  (*__errno_location ()) = 0;
  stat = system(cmd);
  if (cmd != ((void*)0))
    return luaL_execresult(L, stat);
  else {
    lua_pushboolean(L, stat);
    return 1;
  }
}

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


extern int luaL_execresult(lua_State *, int);
extern int * __errno_location();
extern void * luaL_checkudata(lua_State *, int, const char *);

extern int io_pclose (lua_State *L) {
  LStream *p = ((LStream *)luaL_checkudata(L, 1, "FILE*"));
  (*__errno_location ()) = 0;
  return luaL_execresult(L, ((void)L, (void)p->f, -1));
}
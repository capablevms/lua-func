
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

extern void lua_settop(lua_State *, int);
extern void l_message(const char *, const char *);
extern const char * lua_tolstring(lua_State *, int, size_t *);

static int report (lua_State *L, int status) {
  if (status != 0) {
    const char *msg = lua_tolstring(L, (-1), ((void*)0));
    l_message(progname, msg);
    lua_settop(L, -(1)-1);
  }
  return status;
}
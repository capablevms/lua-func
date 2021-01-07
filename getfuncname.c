
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



extern const char * funcnamefromcode(lua_State *, CallInfo *, const char **);

static const char *getfuncname (lua_State *L, CallInfo *ci, const char **name) {
  if (ci == ((void*)0))
    return ((void*)0);
  else if (ci->callstatus & (1<<7)) {
    *name = "__gc";
    return "metamethod";
  }

  else if (!(ci->callstatus & (1<<5)) && (!((ci->previous)->callstatus & (1<<1))))
    return funcnamefromcode(L, ci->previous, name);
  else return ((void*)0);
}
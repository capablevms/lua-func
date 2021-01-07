
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



extern int luaD_growstack(lua_State *, int, int);

extern int lua_checkstack (lua_State *L, int n) {
  int res;
  CallInfo *ci;
  ((void) 0);
  ci = L->ci;
  ((void)L, ((void)0));
  if (L->stack_last - L->top > n)
    res = 1;
  else {
    int inuse = ((int)((L->top - L->stack))) + 5;
    if (inuse > 1000000 - n)
      res = 0;
    else
      res = luaD_growstack(L, n, 0);
  }
  if (res && ci->top < L->top + n)
    ci->top = L->top + n;
  ((void) 0);
  return res;
}

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



extern int luaF_close(lua_State *, StkId, int);

extern void lua_settop (lua_State *L, int idx) {
  CallInfo *ci;
  StkId func;
  ptrdiff_t diff;
  ((void) 0);
  ci = L->ci;
  func = ci->func;
  if (idx >= 0) {
    ((void)L, ((void)0));
    diff = ((func + 1) + idx) - L->top;
    for (; diff > 0; diff--)
      (((&(L->top++)->val))->tt_=(((0) | ((0) << 4))));
  }
  else {
    ((void)L, ((void)0));
    diff = idx + 1;
  }
  if (diff < 0 && ((ci->nresults) < (-1)))
    luaF_close(L, L->top + diff, 0);
  L->top += diff;
  ((void) 0);
}

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



extern void luaD_callnoyield(lua_State *, StkId, int);
extern void luaD_call(lua_State *, StkId, int);

extern void lua_callk (lua_State *L, int nargs, int nresults,
                        lua_KContext ctx, lua_KFunction k) {
  StkId func;
  ((void) 0);
  ((void)L, ((void)0));

  ((void)L, ((void)0));
  ((void)L, ((void)0));
  ((void)L, ((void)0));
  func = L->top - (nargs+1);
  if (k != ((void*)0) && (((L)->nCcalls & 0xffff0000) == 0)) {
    L->ci->u.c.k = k;
    L->ci->u.c.ctx = ctx;
    luaD_call(L, func, nresults);
  }
  else
    luaD_callnoyield(L, func, nresults);
  { if ((nresults) <= (-1) && L->ci->top < L->top) L->ci->top = L->top; };
  ((void) 0);
}
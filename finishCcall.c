
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



extern void luaD_poscall(lua_State *, CallInfo *, int);

static void finishCcall (lua_State *L, int status) {
  CallInfo *ci = L->ci;
  int n;

  ((void)0);

  ((void)0);
  if (ci->callstatus & (1<<4)) {
    ci->callstatus &= ~(1<<4);
    L->errfunc = ci->u.c.old_errfunc;
  }


  { if ((ci->nresults) <= (-1) && L->ci->top < L->top) L->ci->top = L->top; };
  ((void) 0);
  n = (*ci->u.c.k)(L, status, ci->u.c.ctx);
  ((void) 0);
  ((void)L, ((void)0));
  luaD_poscall(L, ci, n);
}
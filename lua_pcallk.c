
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

struct CallS {  /* data to 'f_call' */
  StkId func;
  int nresults;
};

extern void luaD_call(lua_State *, StkId, int);
extern int luaD_pcall(lua_State *, Pfunc, void *, ptrdiff_t, ptrdiff_t);
extern StkId index2stack(lua_State *, int);

extern void f_call (lua_State *L, void *ud);


extern int lua_pcallk (lua_State *L, int nargs, int nresults, int errfunc,
                        lua_KContext ctx, lua_KFunction k) {
  struct CallS c;
  int status;
  ptrdiff_t func;
  ((void) 0);
  ((void)L, ((void)0));

  ((void)L, ((void)0));
  ((void)L, ((void)0));
  ((void)L, ((void)0));
  if (errfunc == 0)
    func = 0;
  else {
    StkId o = index2stack(L, errfunc);
    ((void)L, ((void)0));
    func = ((char *)(o) - (char *)L->stack);
  }
  c.func = L->top - (nargs+1);
  if (k == ((void*)0) || !(((L)->nCcalls & 0xffff0000) == 0)) {
    c.nresults = nresults;
    status = luaD_pcall(L, f_call, &c, ((char *)(c.func) - (char *)L->stack), func);
  }
  else {
    CallInfo *ci = L->ci;
    ci->u.c.k = k;
    ci->u.c.ctx = ctx;

    ci->u2.funcidx = ((int)((((char *)(c.func) - (char *)L->stack))));
    ci->u.c.old_errfunc = L->errfunc;
    L->errfunc = func;
    ((ci->callstatus) = ((ci->callstatus) & ~(1<<0)) | (L->allowhook));
    ci->callstatus |= (1<<4);
    luaD_call(L, c.func, nresults);
    ci->callstatus &= ~(1<<4);
    L->errfunc = ci->u.c.old_errfunc;
    status = 0;
  }
  { if ((nresults) <= (-1) && L->ci->top < L->top) L->ci->top = L->top; };
  ((void) 0);
  return status;
}
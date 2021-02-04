
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



extern void luaD_tryfuncTM(lua_State *, StkId);
extern int luaD_growstack(lua_State *, int, int);
extern void luaC_step(lua_State *);
extern CallInfo * luaE_extendCI(lua_State *);
extern int luaD_growstack(lua_State *, int, int);
extern void luaC_step(lua_State *);
extern void luaD_poscall(lua_State *, CallInfo *, int);
extern void luaD_hook(lua_State *, int, int, int, int);
extern CallInfo * luaE_extendCI(lua_State *);
extern int luaD_growstack(lua_State *, int, int);
extern void luaC_step(lua_State *);

CallInfo *luaD_precall (lua_State *L, StkId func, int nresults) {
  lua_CFunction f;
 retry:
  switch ((((((&(func)->val))->tt_)) & 0x3F)) {
    case ((6) | ((2) << 4)):
      f = ((&((((union GCUnion *)(((((&(func)->val))->value_).gc))))->cl.c)))->f;
      goto Cfunc;
    case ((6) | ((1) << 4)):
      f = ((((&(func)->val))->value_).f);
     Cfunc: {
      int n;
      CallInfo *ci;
      if (L->stack_last - L->top <= (20)) { ptrdiff_t t__ = ((char *)(func) - (char *)L->stack); { if ((L->l_G)->GCdebt > 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); }; luaD_growstack(L, 20, 1); func = ((StkId)((char *)L->stack + (t__))); } else { ((void)0); };
      L->ci = ci = (L->ci->next ? L->ci->next : luaE_extendCI(L));
      ci->nresults = nresults;
      ci->callstatus = (1<<1);
      ci->top = L->top + 20;
      ci->func = func;
      ((void)0);
      if (L->hookmask & (1 << 0)) {
        int narg = ((int)((L->top - func))) - 1;
        luaD_hook(L, 0, -1, 1, narg);
      }
      ((void) 0);
      n = (*f)(L);
      ((void) 0);
      ((void)L, ((void)0));
      luaD_poscall(L, ci, n);
      return ((void*)0);
    }
    case ((6) | ((0) << 4)): {
      CallInfo *ci;
      Proto *p = ((&((((union GCUnion *)(((((&(func)->val))->value_).gc))))->cl.l)))->p;
      int narg = ((int)((L->top - func))) - 1;
      int nfixparams = p->numparams;
      int fsize = p->maxstacksize;
      if (L->stack_last - L->top <= (fsize)) { ptrdiff_t t__ = ((char *)(func) - (char *)L->stack); { if ((L->l_G)->GCdebt > 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); }; luaD_growstack(L, fsize, 1); func = ((StkId)((char *)L->stack + (t__))); } else { ((void)0); };
      L->ci = ci = (L->ci->next ? L->ci->next : luaE_extendCI(L));
      ci->nresults = nresults;
      ci->u.l.savedpc = p->code;
      ci->top = func + 1 + fsize;
      ci->func = func;
      L->ci = ci;
      for (; narg < nfixparams; narg++)
        (((&(L->top++)->val))->tt_=(((0) | ((0) << 4))));
      ((void)0);
      return ci;
    }
    default: {
      if (L->stack_last - L->top <= (1)) { ptrdiff_t t__ = ((char *)(func) - (char *)L->stack); { if ((L->l_G)->GCdebt > 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); }; luaD_growstack(L, 1, 1); func = ((StkId)((char *)L->stack + (t__))); } else { ((void)0); };
      luaD_tryfuncTM(L, func);
      goto retry;
    }
  }
}
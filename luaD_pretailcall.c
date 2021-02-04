
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
extern void luaC_step(lua_State *);

void luaD_pretailcall (lua_State *L, CallInfo *ci, StkId func, int narg1) {
  Proto *p = ((&((((union GCUnion *)(((((&(func)->val))->value_).gc))))->cl.l)))->p;
  int fsize = p->maxstacksize;
  int nfixparams = p->numparams;
  int i;
  for (i = 0; i < narg1; i++)
    { TValue *io1=((&(ci->func + i)->val)); const TValue *io2=((&(func + i)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
  if (L->stack_last - L->top <= ((fsize))) { { if ((L->l_G)->GCdebt > 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); }; luaD_growstack(L, (fsize), 1); (void)0; } else { ((void)0); };
  func = ci->func;
  for (; narg1 <= nfixparams; narg1++)
    (((&(func + narg1)->val))->tt_=(((0) | ((0) << 4))));
  ci->top = func + 1 + fsize;
  ((void)0);
  ci->u.l.savedpc = p->code;
  ci->callstatus |= (1<<5);
  L->top = func + narg1;
}
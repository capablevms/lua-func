
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

void luaT_adjustvarargs (lua_State *L, int nfixparams, CallInfo *ci,
                         const Proto *p) {
  int i;
  int actual = ((int)((L->top - ci->func))) - 1;
  int nextra = actual - nfixparams;
  ci->u.l.nextraargs = nextra;
  if (L->stack_last - L->top <= (p->maxstacksize + 1)) { (void)0; luaD_growstack(L, p->maxstacksize + 1, 1); (void)0; } else { ((void)0); };

  { TValue *io1=((&(L->top++)->val)); const TValue *io2=((&(ci->func)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };

  for (i = 1; i <= nfixparams; i++) {
    { TValue *io1=((&(L->top++)->val)); const TValue *io2=((&(ci->func + i)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
    (((&(ci->func + i)->val))->tt_=(((0) | ((0) << 4))));
  }
  ci->func += actual + 1;
  ci->top += actual + 1;
  ((void)0);
}

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

void luaT_getvarargs (lua_State *L, CallInfo *ci, StkId where, int wanted) {
  int i;
  int nextra = ci->u.l.nextraargs;
  if (wanted < 0) {
    wanted = nextra;
    if (L->stack_last - L->top <= (nextra)) { ptrdiff_t t__ = ((char *)(where) - (char *)L->stack); { if ((L->l_G)->GCdebt > 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); }; luaD_growstack(L, nextra, 1); where = ((StkId)((char *)L->stack + (t__))); } else { ((void)0); };
    L->top = where + nextra;
  }
  for (i = 0; i < wanted && i < nextra; i++)
    { TValue *io1=((&(where + i)->val)); const TValue *io2=((&(ci->func - nextra + i)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
  for (; i < wanted; i++)
    (((&(where + i)->val))->tt_=(((0) | ((0) << 4))));
}
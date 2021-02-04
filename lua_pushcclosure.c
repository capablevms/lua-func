
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



extern void luaC_step(lua_State *);
extern CClosure * luaF_newCclosure(lua_State *, int);

extern void lua_pushcclosure (lua_State *L, lua_CFunction fn, int n) {
  ((void) 0);
  if (n == 0) {
    { TValue *io=((&(L->top)->val)); ((io)->value_).f=(fn); ((io)->tt_=(((6) | ((1) << 4)))); };
    {L->top++; ((void)L, ((void)0));};
  }
  else {
    CClosure *cl;
    ((void)L, ((void)0));
    ((void)L, ((void)0));
    cl = luaF_newCclosure(L, n);
    cl->f = fn;
    L->top -= n;
    while (n--) {
      { TValue *io1=(&cl->upvalue[n]); const TValue *io2=((&(L->top + n)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };

      ((void)0);
    }
    { TValue *io = ((&(L->top)->val)); CClosure *x_ = (cl); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((((6) | ((2) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
    {L->top++; ((void)L, ((void)0));};
    { if ((L->l_G)->GCdebt > 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); };
  }
  ((void) 0);
}
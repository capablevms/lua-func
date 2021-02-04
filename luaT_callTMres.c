
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

void luaT_callTMres (lua_State *L, const TValue *f, const TValue *p1,
                     const TValue *p2, StkId res) {
  ptrdiff_t result = ((char *)(res) - (char *)L->stack);
  StkId func = L->top;
  { TValue *io1=((&(func)->val)); const TValue *io2=(f); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
  { TValue *io1=((&(func + 1)->val)); const TValue *io2=(p1); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
  { TValue *io1=((&(func + 2)->val)); const TValue *io2=(p2); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
  L->top += 3;

  if ((!((L->ci)->callstatus & ((1<<1) | (1<<3)))))
    luaD_call(L, func, 1);
  else
    luaD_callnoyield(L, func, 1);
  res = ((StkId)((char *)L->stack + (result)));
  { TValue *io1=((&(res)->val)); const TValue *io2=((&(--L->top)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
}
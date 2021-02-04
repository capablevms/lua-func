
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



extern void luaD_throw(lua_State *, int);
extern void luaD_callnoyield(lua_State *, StkId, int);

void __attribute__((noreturn)) luaG_errormsg (lua_State *L) {
  if (L->errfunc != 0) {
    StkId errfunc = ((StkId)((char *)L->stack + (L->errfunc)));
    ((void)0);
    { TValue *io1=((&(L->top)->val)); const TValue *io2=((&(L->top - 1)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
    { TValue *io1=((&(L->top - 1)->val)); const TValue *io2=((&(errfunc)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
    L->top++;
    luaD_callnoyield(L, L->top - 2, 1);
  }
  luaD_throw(L, 2);
}
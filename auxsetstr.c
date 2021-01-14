
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



extern void luaV_finishset(lua_State *, const TValue *, TValue *, TValue *, const TValue *);
extern void luaC_barrierback_(lua_State *, GCObject *);
extern const TValue * luaH_getstr(Table *, TString *);
extern TString * luaS_new(lua_State *, const char *);

extern void auxsetstr (lua_State *L, const TValue *t, const char *k) {
  const TValue *slot;
  TString *str = luaS_new(L, k);
  ((void)L, ((void)0));
  if ((!((((t))->tt_) == (((((5) | ((0) << 4))) | (1 << 6)))) ? (slot = ((void*)0), 0) : (slot = luaH_getstr(((&((((union GCUnion *)((((t)->value_).gc))))->h))), str), !(((((((slot))->tt_)) & 0x0F)) == (0))))) {
    { { TValue *io1=(((TValue *)(slot))); const TValue *io2=((&(L->top - 1)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); }; ( (((((&(L->top - 1)->val))->tt_) & (1 << 6)) && ((((((t)->value_).gc))->marked) & ((1<<(5)))) && (((((((&(L->top - 1)->val))->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrierback_(L,(((t)->value_).gc)) : ((void)((0)))); };
    L->top--;
  }
  else {
    { TValue *io = ((&(L->top)->val)); TString *x_ = (str); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((x_->tt) | (1 << 6)))); ((void)L, ((void)0)); };
    {L->top++; ((void)L, ((void)0));};
    luaV_finishset(L, t, (&(L->top - 1)->val), (&(L->top - 2)->val), slot);
    L->top -= 2;
  }
  ((void) 0);
}
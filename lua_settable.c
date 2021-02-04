
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
extern const TValue * luaH_get(Table *, const TValue *);
extern TValue * index2value(lua_State *, int);

extern void lua_settable (lua_State *L, int idx) {
  TValue *t;
  const TValue *slot;
  ((void) 0);
  ((void)L, ((void)0));
  t = index2value(L, idx);
  if ((!((((t))->tt_) == (((((5) | ((0) << 4))) | (1 << 6)))) ? (slot = ((void*)0), 0) : (slot = luaH_get(((&((((union GCUnion *)((((t)->value_).gc))))->h))), (&(L->top - 2)->val)), !(((((((slot))->tt_)) & 0x0F)) == (0))))) {
    { { TValue *io1=(((TValue *)(slot))); const TValue *io2=((&(L->top - 1)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); }; ( (((((&(L->top - 1)->val))->tt_) & (1 << 6)) && ((((((t)->value_).gc))->marked) & ((1<<(5)))) && (((((((&(L->top - 1)->val))->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrierback_(L,(((t)->value_).gc)) : ((void)((0)))); };
  }
  else
    luaV_finishset(L, t, (&(L->top - 2)->val), (&(L->top - 1)->val), slot);
  L->top -= 2;
  ((void) 0);
}
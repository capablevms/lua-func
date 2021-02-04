
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



extern void luaC_barrierback_(lua_State *, GCObject *);
extern TValue * luaH_set(lua_State *, Table *, const TValue *);
extern Table * gettable(lua_State *, int);

extern void aux_rawset (lua_State *L, int idx, TValue *key, int n) {
  Table *t;
  TValue *slot;
  ((void) 0);
  ((void)L, ((void)0));
  t = gettable(L, idx);
  slot = luaH_set(L, t, key);
  { TValue *io1=(slot); const TValue *io2=((&(L->top - 1)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
  ((t)->flags &= ~(~(~0u << (TM_EQ + 1))));
  ( (((((&(L->top - 1)->val))->tt_) & (1 << 6)) && ((((&(((union GCUnion *)((t)))->gc)))->marked) & ((1<<(5)))) && (((((((&(L->top - 1)->val))->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrierback_(L,(&(((union GCUnion *)((t)))->gc))) : ((void)((0))));
  L->top -= n;
  ((void) 0);
}
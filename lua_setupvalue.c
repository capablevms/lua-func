
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



extern void luaC_barrier_(lua_State *, GCObject *, GCObject *);
extern const char * aux_upvalue(TValue *, int, TValue **, GCObject **);
extern TValue * index2value(lua_State *, int);

extern const char *lua_setupvalue (lua_State *L, int funcindex, int n) {
  const char *name;
  TValue *val = ((void*)0);
  GCObject *owner = ((void*)0);
  TValue *fi;
  ((void) 0);
  fi = index2value(L, funcindex);
  ((void)L, ((void)0));
  name = aux_upvalue(fi, n, &val, &owner);
  if (name) {
    L->top--;
    { TValue *io1=(val); const TValue *io2=((&(L->top)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
    ( ((((val)->tt_) & (1 << 6)) && (((owner)->marked) & ((1<<(5)))) && ((((((val)->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(&(((union GCUnion *)((owner)))->gc)),(((val)->value_).gc)) : ((void)((0))));
  }
  ((void) 0);
  return name;
}
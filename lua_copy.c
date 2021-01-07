
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
extern TValue * index2value(lua_State *, int);
extern TValue * index2value(lua_State *, int);

extern void lua_copy (lua_State *L, int fromidx, int toidx) {
  TValue *fr, *to;
  ((void) 0);
  fr = index2value(L, fromidx);
  to = index2value(L, toidx);
  ((void)L, ((void)0));
  { TValue *io1=(to); const TValue *io2=(fr); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
  if (((toidx) < (-1000000 - 1000)))
    ( ((((fr)->tt_) & (1 << 6)) && (((((&((((union GCUnion *)(((((&(L->ci->func)->val))->value_).gc))))->cl.c))))->marked) & ((1<<(5)))) && ((((((fr)->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(&(((union GCUnion *)((((&((((union GCUnion *)(((((&(L->ci->func)->val))->value_).gc))))->cl.c))))))->gc)),(((fr)->value_).gc)) : ((void)((0))));


  ((void) 0);
}
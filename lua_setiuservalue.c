
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
extern TValue * index2value(lua_State *, int);

extern int lua_setiuservalue (lua_State *L, int idx, int n) {
  TValue *o;
  int res;
  ((void) 0);
  ((void)L, ((void)0));
  o = index2value(L, idx);
  ((void)L, ((void)0));
  if (!(((unsigned int)((n))) - 1u < ((unsigned int)((((&((((union GCUnion *)((((o)->value_).gc))))->u)))->nuvalue)))))
    res = 0;
  else {
    { TValue *io1=(&((&((((union GCUnion *)((((o)->value_).gc))))->u)))->uv[n - 1].uv); const TValue *io2=((&(L->top - 1)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
    ( (((((&(L->top - 1)->val))->tt_) & (1 << 6)) && ((((((o)->value_).gc))->marked) & ((1<<(5)))) && (((((((&(L->top - 1)->val))->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrierback_(L,(((o)->value_).gc)) : ((void)((0))));
    res = 1;
  }
  L->top--;
  ((void) 0);
  return res;
}
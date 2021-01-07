
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



extern TValue * index2value(lua_State *, int);

extern int lua_getiuservalue (lua_State *L, int idx, int n) {
  TValue *o;
  int t;
  ((void) 0);
  o = index2value(L, idx);
  ((void)L, ((void)0));
  if (n <= 0 || n > ((&((((union GCUnion *)((((o)->value_).gc))))->u)))->nuvalue) {
    (((&(L->top)->val))->tt_=(((0) | ((0) << 4))));
    t = (-1);
  }
  else {
    { TValue *io1=((&(L->top)->val)); const TValue *io2=(&((&((((union GCUnion *)((((o)->value_).gc))))->u)))->uv[n - 1].uv); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
    t = ((((((&(L->top)->val))->tt_)) & 0x0F));
  }
  {L->top++; ((void)L, ((void)0));};
  ((void) 0);
  return t;
}
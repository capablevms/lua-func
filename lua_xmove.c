
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




extern void lua_xmove (lua_State *from, lua_State *to, int n) {
  int i;
  if (from == to) return;
  ((void) 0);
  ((void)from, ((void)0));
  ((void)from, ((void)0));
  ((void)from, ((void)0));
  from->top -= n;
  for (i = 0; i < n; i++) {
    { TValue *io1=((&(to->top)->val)); const TValue *io2=((&(from->top + i)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)to, ((void)0)); ((void)0); };
    to->top++;
  }
  ((void) 0);
}
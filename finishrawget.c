
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




extern int finishrawget (lua_State *L, const TValue *val) {
  if ((((((((val))->tt_)) & 0x0F)) == (0)))
    (((&(L->top)->val))->tt_=(((0) | ((0) << 4))));
  else
    { TValue *io1=((&(L->top)->val)); const TValue *io2=(val); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
  {L->top++; ((void)L, ((void)0));};
  ((void) 0);
  return ((((((&(L->top - 1)->val))->tt_)) & 0x0F));
}
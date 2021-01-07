
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



extern const TValue * luaT_gettmbyobj(lua_State *, const TValue *, TMS);

static int prepclosingmethod (lua_State *L, TValue *obj, TValue *err) {
  StkId top = L->top;
  const TValue *tm = luaT_gettmbyobj(L, obj, TM_CLOSE);
  if ((((((((tm))->tt_)) & 0x0F)) == (0)))
    return 0;
  { TValue *io1=((&(top)->val)); const TValue *io2=(tm); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
  { TValue *io1=((&(top + 1)->val)); const TValue *io2=(obj); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
  { TValue *io1=((&(top + 2)->val)); const TValue *io2=(err); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
  L->top = top + 3;
  return 1;
}
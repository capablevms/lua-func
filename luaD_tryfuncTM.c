
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



extern void luaG_typeerror(lua_State *, const TValue *, const char *);
extern long __builtin_expect(long, long);
extern const TValue * luaT_gettmbyobj(lua_State *, const TValue *, TMS);

void luaD_tryfuncTM (lua_State *L, StkId func) {
  const TValue *tm = luaT_gettmbyobj(L, (&(func)->val), TM_CALL);
  StkId p;
  if ((__builtin_expect((((((((((tm))->tt_)) & 0x0F)) == (0))) != 0), 0)))
    luaG_typeerror(L, (&(func)->val), "call");
  for (p = L->top; p > func; p--)
    { TValue *io1=((&(p)->val)); const TValue *io2=((&(p-1)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
  L->top++;
  { TValue *io1=((&(func)->val)); const TValue *io2=(tm); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
}
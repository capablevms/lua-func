
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



extern void luaC_step(lua_State *);
extern TString * luaS_newlstr(lua_State *, const char *, size_t);
extern void luaV_concat(lua_State *, int);

extern void lua_concat (lua_State *L, int n) {
  ((void) 0);
  ((void)L, ((void)0));
  if (n > 0)
    luaV_concat(L, n);
  else {
    { TValue *io = ((&(L->top)->val)); TString *x_ = (luaS_newlstr(L, "", 0)); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((x_->tt) | (1 << 6)))); ((void)L, ((void)0)); };
    {L->top++; ((void)L, ((void)0));};
  }
  { if ((L->l_G)->GCdebt > 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); };
  ((void) 0);
}

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
extern TValue * luaH_set(lua_State *, Table *, const TValue *);
extern TString * luaS_newlstr(lua_State *, const char *, size_t);

TString *luaX_newstring (LexState *ls, const char *str, size_t l) {
  lua_State *L = ls->L;
  TValue *o;
  TString *ts = luaS_newlstr(L, str, l);
  { TValue *io = ((&(L->top++)->val)); TString *x_ = (ts); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((x_->tt) | (1 << 6)))); ((void)L, ((void)0)); };
  o = luaH_set(L, ls->h, (&(L->top - 1)->val));
  if ((((((((o))->tt_)) & 0x0F)) == (0))) {


    ((o)->tt_=(((1) | ((1) << 4))));
    { if ((L->l_G)->GCdebt > 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); };
  }
  else {
    ts = ((&((((union GCUnion *)((((((Node *)((o))))->u.key_val).gc))))->ts)));
  }
  L->top--;
  return ts;
}
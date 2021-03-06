
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
extern TString * luaS_new(lua_State *, const char *);

extern const char *lua_pushlstring (lua_State *L, const char *s, size_t len) {
  TString *ts;
  ((void) 0);
  ts = (len == 0) ? luaS_new(L, "") : luaS_newlstr(L, s, len);
  { TValue *io = ((&(L->top)->val)); TString *x_ = (ts); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((x_->tt) | (1 << 6)))); ((void)L, ((void)0)); };
  {L->top++; ((void)L, ((void)0));};
  { if ((L->l_G)->GCdebt > 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); };
  ((void) 0);
  return ((ts)->contents);
}
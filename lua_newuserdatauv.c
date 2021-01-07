
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
extern Udata * luaS_newudata(lua_State *, size_t, int);

extern void *lua_newuserdatauv (lua_State *L, size_t size, int nuvalue) {
  Udata *u;
  ((void) 0);
  ((void)L, ((void)0));
  u = luaS_newudata(L, size, nuvalue);
  { TValue *io = ((&(L->top)->val)); Udata *x_ = (u); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((((7) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
  {L->top++; ((void)L, ((void)0));};
  { if ((L->l_G)->GCdebt > 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); };
  ((void) 0);
  return (((char *)((u))) + (((u)->nuvalue) == 0 ? __builtin_offsetof(Udata0, bindata) : __builtin_offsetof(Udata, uv) + (sizeof(UValue) * ((u)->nuvalue))));
}
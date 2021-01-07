
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



extern void luaE_warnerror(lua_State *, const char *);
extern long __builtin_expect(long, long);
extern int luaD_pcall(lua_State *, Pfunc, void *, ptrdiff_t, ptrdiff_t);
extern const TValue * luaT_gettmbyobj(lua_State *, const TValue *, TMS);
extern GCObject * udata2finalize(global_State *);

static void GCTM (lua_State *L) {
  global_State *g = (L->l_G);
  const TValue *tm;
  TValue v;
  ((void)0);
  { TValue *io = (&v); GCObject *i_g=(udata2finalize(g)); ((io)->value_).gc = i_g; ((io)->tt_=(((i_g->tt) | (1 << 6)))); };
  tm = luaT_gettmbyobj(L, &v, TM_GC);
  if (!(((((((tm))->tt_)) & 0x0F)) == (0))) {
    int status;
    lu_byte oldah = L->allowhook;
    int running = g->gcrunning;
    L->allowhook = 0;
    g->gcrunning = 0;
    { TValue *io1=((&(L->top++)->val)); const TValue *io2=(tm); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
    { TValue *io1=((&(L->top++)->val)); const TValue *io2=(&v); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
    L->ci->callstatus |= (1<<7);
    status = luaD_pcall(L, dothecall, ((void*)0), ((char *)(L->top - 2) - (char *)L->stack), 0);
    L->ci->callstatus &= ~(1<<7);
    L->allowhook = oldah;
    g->gcrunning = running;
    if ((__builtin_expect(((status != 0) != 0), 0))) {
      luaE_warnerror(L, "__gc metamethod");
      L->top--;
    }
  }
}
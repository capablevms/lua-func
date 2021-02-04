
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



extern void luaH_setint(lua_State *, Table *, lua_Integer, TValue *);
extern int nextline(const Proto *, int, int);
extern Table * luaH_new(lua_State *);

extern void collectvalidlines (lua_State *L, Closure *f) {
  if (((f) == ((void*)0) || (f)->c.tt == ((6) | ((2) << 4)))) {
    (((&(L->top)->val))->tt_=(((0) | ((0) << 4))));
    {L->top++; ((void)L, ((void)0));};
  }
  else {
    int i;
    TValue v;
    const Proto *p = f->l.p;
    int currentline = p->linedefined;
    Table *t = luaH_new(L);
    { TValue *io = ((&(L->top)->val)); Table *x_ = (t); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((((5) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
    {L->top++; ((void)L, ((void)0));};
    ((&v)->tt_=(((1) | ((1) << 4))));
    for (i = 0; i < p->sizelineinfo; i++) {
      currentline = nextline(p, currentline, i);
      luaH_setint(L, t, currentline, &v);
    }
  }
}
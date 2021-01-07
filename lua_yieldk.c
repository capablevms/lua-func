
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



extern void luaD_throw(lua_State *, int);
extern void luaG_runerror(lua_State *, const char *, ...);
extern void luaG_runerror(lua_State *, const char *, ...);
extern long __builtin_expect(long, long);

extern int lua_yieldk (lua_State *L, int nresults, lua_KContext ctx,
                        lua_KFunction k) {
  CallInfo *ci;
  ((void)L);
  ((void) 0);
  ci = L->ci;
  ((void)L, ((void)0));
  if ((__builtin_expect(((!(((L)->nCcalls & 0xffff0000) == 0)) != 0), 0))) {
    if (L != (L->l_G)->mainthread)
      luaG_runerror(L, "attempt to yield across a C-call boundary");
    else
      luaG_runerror(L, "attempt to yield from outside a coroutine");
  }
  L->status = 1;
  if ((!((ci)->callstatus & (1<<1)))) {
    ((void)0);
    ((void)L, ((void)0));
    ci->u2.nyield = 0;
  }
  else {
    if ((ci->u.c.k = k) != ((void*)0))
      ci->u.c.ctx = ctx;
    ci->u2.nyield = nresults;
    luaD_throw(L, 1);
  }
  ((void)0);
  ((void) 0);
  return 0;
}
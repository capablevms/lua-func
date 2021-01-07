
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



extern void unroll(lua_State *, void *);
extern void luaD_poscall(lua_State *, CallInfo *, int);
extern void luaV_execute(lua_State *, CallInfo *);
extern void luaE_incCstack(lua_State *);
extern void docall(lua_State *, StkId, int, int);

static void resume (lua_State *L, void *ud) {
  int n = *(((int*)(ud)));
  StkId firstArg = L->top - n;
  CallInfo *ci = L->ci;
  if (L->status == 0)
    docall(L, firstArg - 1, (-1), 1);
  else {
    ((void)0);
    L->status = 0;
    luaE_incCstack(L);
    if ((!((ci)->callstatus & (1<<1))))
      luaV_execute(L, ci);
    else {
      if (ci->u.c.k != ((void*)0)) {
        ((void) 0);
        n = (*ci->u.c.k)(L, 1, ci->u.c.ctx);
        ((void) 0);
        ((void)L, ((void)0));
      }
      luaD_poscall(L, ci, n);
    }
    unroll(L, ((void*)0));
  }
}
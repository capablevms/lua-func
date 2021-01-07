
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



extern void * luaM_malloc_(lua_State *, size_t, int);

static void stack_init (lua_State *L1, lua_State *L) {
  int i; CallInfo *ci;

  L1->stack = ((StackValue*)(luaM_malloc_(L, ((2*20) + 5)*sizeof(StackValue), 0)));
  for (i = 0; i < (2*20); i++)
    (((&(L1->stack + i)->val))->tt_=(((0) | ((0) << 4))));
  L1->top = L1->stack;
  L1->stack_last = L1->stack + (2*20);

  ci = &L1->base_ci;
  ci->next = ci->previous = ((void*)0);
  ci->callstatus = (1<<1);
  ci->func = L1->top;
  ci->u.c.k = ((void*)0);
  ci->nresults = 0;
  (((&(L1->top)->val))->tt_=(((0) | ((0) << 4))));
  L1->top++;
  ci->top = L1->top + 20;
  L1->ci = ci;
}
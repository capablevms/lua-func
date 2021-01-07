
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



extern void stack_init(lua_State *, lua_State *);
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern void preinit_thread(lua_State *, global_State *);
extern void * luaM_malloc_(lua_State *, size_t, int);
extern void luaC_step(lua_State *);

extern lua_State *lua_newthread (lua_State *L) {
  global_State *g;
  lua_State *L1;
  ((void) 0);
  g = (L->l_G);
  { if ((L->l_G)->GCdebt > 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); };

  L1 = &((LX *)(luaM_malloc_(L, (sizeof(LX)), 8)))->l;
  L1->marked = ((lu_byte)(((g)->currentwhite & ((1<<(3)) | (1<<(4))))));
  L1->tt = ((8) | ((0) << 4));

  L1->next = g->allgc;
  g->allgc = (&(((union GCUnion *)((L1)))->gc));

  { TValue *io = ((&(L->top)->val)); lua_State *x_ = (L1); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((((8) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
  {L->top++; ((void)L, ((void)0));};
  preinit_thread(L1, g);
  L1->nCcalls = 0;
  L1->hookmask = L->hookmask;
  L1->basehookcount = L->basehookcount;
  L1->hook = L->hook;
  (L1->hookcount = L1->basehookcount);

  memcpy(((void *)((char *)(L1) - (sizeof(void *)))), ((void *)((char *)(g->mainthread) - (sizeof(void *)))),
         (sizeof(void *)));
  ((void)L);
  stack_init(L1, L);
  ((void) 0);
  return L1;
}
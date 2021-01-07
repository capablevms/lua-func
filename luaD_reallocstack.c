
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



extern void correctstack(lua_State *, StkId, StkId);
extern void luaD_throw(lua_State *, int);
extern long __builtin_expect(long, long);
extern void * luaM_realloc_(lua_State *, void *, size_t, size_t);

int luaD_reallocstack (lua_State *L, int newsize, int raiseerror) {
  int lim = ((int)(((L)->stack_last - (L)->stack)));
  StkId newstack = (((StackValue *)(luaM_realloc_(L, L->stack, ((size_t)((lim + 5))) * sizeof(StackValue), ((size_t)((newsize + 5))) * sizeof(StackValue)))));

  ((void)0);
  if ((__builtin_expect(((newstack == ((void*)0)) != 0), 0))) {
    if (raiseerror)
      luaD_throw(L, 4);
    else return 0;
  }
  for (; lim < newsize; lim++)
    (((&(newstack + lim)->val))->tt_=(((0) | ((0) << 4))));
  correctstack(L, L->stack, newstack);
  L->stack = newstack;
  L->stack_last = L->stack + newsize;
  return 1;
}

#include "lprefix.h"
#include "lua.h"
#include "lapi.h"
#include "ldebug.h"
#include "ldo.h"
#include "lfunc.h"
#include "lgc.h"
#include "lmem.h"
#include "lobject.h"
#include "lopcodes.h"
#include "lparser.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "ltm.h"
#include "lundump.h"
#include "lvm.h"
#include "lzio.h"

extern void unroll(lua_State *, void *);

/*
** Call a function (C or Lua). 'inc' can be 1 (increment number
** of recursive invocations in the C stack) or nyci (the same plus
** increment number of non-yieldable calls).
*/
static void docall (lua_State *L, StkId func, int nResults, int inc) {
  CallInfo *ci;
  L->nCcalls += inc;
  if (unlikely(getCcalls(L) >= LUAI_MAXCCALLS))
    luaE_checkcstack(L);
  if ((ci = luaD_precall(L, func, nResults)) != NULL) {  /* Lua function? */
    ci->callstatus = CIST_FRESH;  /* mark that it is a "fresh" execute */
    luaV_execute(L, ci);  /* call it */
  }
  L->nCcalls -= inc;
}


/*
** External interface for 'docall'
*/
extern void luaD_call (lua_State *L, StkId func, int nResults) {
  return docall(L, func, nResults, 1);
}


/*
** Similar to 'luaD_call', but does not allow yields during the call.
*/
extern void luaD_callnoyield (lua_State *L, StkId func, int nResults) {
  return docall(L, func, nResults, nyci);
}

/*
** Do the work for 'lua_resume' in protected mode. Most of the work
** depends on the status of the coroutine: initial state, suspended
** inside a hook, or regularly suspended (optionally with a continuation
** function), plus erroneous cases: non-suspended coroutine or dead
** coroutine.
*/
extern void resume (lua_State *L, void *ud) {
  int n = *(cast(int*, ud));  /* number of arguments */
  StkId firstArg = L->top - n;  /* first argument */
  CallInfo *ci = L->ci;
  if (L->status == LUA_OK)  /* starting a coroutine? */
    docall(L, firstArg - 1, LUA_MULTRET, 1);  /* just call its body */
  else {  /* resuming from previous yield */
    lua_assert(L->status == LUA_YIELD);
    L->status = LUA_OK;  /* mark that it is running (again) */
    luaE_incCstack(L);  /* control the C stack */
    if (isLua(ci))  /* yielded inside a hook? */
      luaV_execute(L, ci);  /* just continue running Lua code */
    else {  /* 'common' yield */
      if (ci->u.c.k != NULL) {  /* does it have a continuation function? */
        lua_unlock(L);
        n = (*ci->u.c.k)(L, LUA_YIELD, ci->u.c.ctx); /* call continuation */
        lua_lock(L);
        api_checknelems(L, n);
      }
      luaD_poscall(L, ci, n);  /* finish 'luaD_call' */
    }
    unroll(L, NULL);  /* run continuation */
  }
}

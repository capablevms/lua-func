
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



extern void luaD_seterrorobj(lua_State *, int, StkId);
extern long __builtin_expect(long, long);
extern int luaD_rawrunprotected(lua_State *, Pfunc, void *);
extern int recover(lua_State *, int);
extern int luaD_rawrunprotected(lua_State *, Pfunc, void *);
extern int resume_error(lua_State *, const char *, int);
extern int resume_error(lua_State *, const char *, int);
extern int resume_error(lua_State *, const char *, int);

extern int lua_resume (lua_State *L, lua_State *from, int nargs,
                                      int *nresults) {
  int status;
  ((void) 0);
  if (L->status == 0) {
    if (L->ci != &L->base_ci)
      return resume_error(L, "cannot resume non-suspended coroutine", nargs);
    else if (L->top - (L->ci->func + 1) == nargs)
      return resume_error(L, "cannot resume dead coroutine", nargs);
  }
  else if (L->status != 1)
    return resume_error(L, "cannot resume dead coroutine", nargs);
  L->nCcalls = (from) ? ((from)->nCcalls & 0xffff) : 0;
  ((void)L);
  ((void)L, ((void)0));
  status = luaD_rawrunprotected(L, resume, &nargs);

  while (((status) > 1) && recover(L, status)) {

    status = luaD_rawrunprotected(L, unroll, &status);
  }
  if ((__builtin_expect(((!((status) > 1)) != 0), 1)))
    ((void)0);
  else {
    L->status = ((lu_byte)((status)));
    luaD_seterrorobj(L, status, L->top);
    L->ci->top = L->top;
  }
  *nresults = (status == 1) ? L->ci->u2.nyield
                                    : ((int)((L->top - (L->ci->func + 1))));
  ((void) 0);
  return status;
}
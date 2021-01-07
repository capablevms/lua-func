
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



extern void moveresults(lua_State *, StkId, int, int);
extern StkId rethook(lua_State *, CallInfo *, StkId, int);

void luaD_poscall (lua_State *L, CallInfo *ci, int nres) {
  if (L->hookmask)
    L->top = rethook(L, ci, L->top - nres, nres);
  L->ci = ci->previous;

  moveresults(L, ci->func, nres, ci->nresults);
}
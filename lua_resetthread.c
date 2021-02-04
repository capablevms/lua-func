
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
extern int luaF_close(lua_State *, StkId, int);

int lua_resetthread (lua_State *L) {
  CallInfo *ci;
  int status;
  ((void) 0);
  L->ci = ci = &L->base_ci;
  (((&(L->stack)->val))->tt_=(((0) | ((0) << 4))));
  ci->func = L->stack;
  ci->callstatus = (1<<1);
  status = luaF_close(L, L->stack, (-2));
  if (status != (-2))
    luaD_seterrorobj(L, status, L->stack + 1);
  else {
    status = 0;
    L->top = L->stack + 1;
  }
  ci->top = L->top + 20;
  L->status = status;
  ((void) 0);
  return status;
}
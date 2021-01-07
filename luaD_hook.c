
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



extern int luaD_growstack(lua_State *, int, int);

void luaD_hook (lua_State *L, int event, int line,
                              int ftransfer, int ntransfer) {
  lua_Hook hook = L->hook;
  if (hook && L->allowhook) {
    int mask = (1<<3);
    CallInfo *ci = L->ci;
    ptrdiff_t top = ((char *)(L->top) - (char *)L->stack);
    ptrdiff_t ci_top = ((char *)(ci->top) - (char *)L->stack);
    lua_Debug ar;
    ar.event = event;
    ar.currentline = line;
    ar.i_ci = ci;
    if (ntransfer != 0) {
      mask |= (1<<8);
      ci->u2.transferinfo.ftransfer = ftransfer;
      ci->u2.transferinfo.ntransfer = ntransfer;
    }
    if (L->stack_last - L->top <= (20)) { (void)0; luaD_growstack(L, 20, 1); (void)0; } else { ((void)0); };
    if (L->top + 20 > ci->top)
      ci->top = L->top + 20;
    L->allowhook = 0;
    ci->callstatus |= mask;
    ((void) 0);
    (*hook)(L, &ar);
    ((void) 0);
    ((void)0);
    L->allowhook = 1;
    ci->top = ((StkId)((char *)L->stack + (ci_top)));
    L->top = ((StkId)((char *)L->stack + (top)));
    ci->callstatus &= ~mask;
  }
}
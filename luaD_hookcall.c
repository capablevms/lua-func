
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



extern void luaD_hook(lua_State *, int, int, int, int);

void luaD_hookcall (lua_State *L, CallInfo *ci) {
  int hook = (ci->callstatus & (1<<5)) ? 4 : 0;
  Proto *p;
  if (!(L->hookmask & (1 << 0)))
    return;
  p = ((&((((union GCUnion *)(((((&(ci->func)->val))->value_).gc))))->cl.l)))->p;
  L->top = ci->top;
  ci->u.l.savedpc++;
  luaD_hook(L, hook, -1, 1, p->numparams);
  ci->u.l.savedpc--;
}
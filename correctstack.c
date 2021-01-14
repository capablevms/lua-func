
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




extern void correctstack (lua_State *L, StkId oldstack, StkId newstack) {
  CallInfo *ci;
  UpVal *up;
  if (oldstack == newstack)
    return;
  L->top = (L->top - oldstack) + newstack;
  for (up = L->openupval; up != ((void*)0); up = up->u.open.next)
    up->v = (&(((((StkId)((up)->v))) - oldstack) + newstack)->val);
  for (ci = L->ci; ci != ((void*)0); ci = ci->previous) {
    ci->top = (ci->top - oldstack) + newstack;
    ci->func = (ci->func - oldstack) + newstack;
    if ((!((ci)->callstatus & (1<<1))))
      ci->u.l.trap = 1;
  }
}
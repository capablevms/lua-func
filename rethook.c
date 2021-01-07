
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

static StkId rethook (lua_State *L, CallInfo *ci, StkId firstres, int nres) {
  ptrdiff_t oldtop = ((char *)(L->top) - (char *)L->stack);
  int delta = 0;
  if ((!((ci)->callstatus & ((1<<1) | (1<<3))))) {
    Proto *p = (((&((((union GCUnion *)(((((&((ci)->func)->val))->value_).gc))))->cl.l))))->p;
    if (p->is_vararg)
      delta = ci->u.l.nextraargs + p->numparams + 1;
    if (L->top < ci->top)
      L->top = ci->top;
  }
  if (L->hookmask & (1 << 1)) {
    int ftransfer;
    ci->func += delta;
    ftransfer = ((unsigned short)(firstres - ci->func));
    luaD_hook(L, 1, -1, ftransfer, nres);
    ci->func -= delta;
  }
  if ((!((ci = ci->previous)->callstatus & (1<<1))))
    L->oldpc = (((int)(((ci->u.l.savedpc) - ((((&((((union GCUnion *)(((((&((ci)->func)->val))->value_).gc))))->cl.l))))->p)->code))) - 1);
  return ((StkId)((char *)L->stack + (oldtop)));
}
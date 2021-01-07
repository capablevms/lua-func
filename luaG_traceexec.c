
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



extern void luaD_throw(lua_State *, int);
extern void luaD_hook(lua_State *, int, int, int, int);
extern int luaG_getfuncline(const Proto *, int);
extern int changedline(const Proto *, int, int);
extern void luaD_hook(lua_State *, int, int, int, int);

int luaG_traceexec (lua_State *L, const Instruction *pc) {
  CallInfo *ci = L->ci;
  lu_byte mask = L->hookmask;
  const Proto *p = (((&((((union GCUnion *)(((((&((ci)->func)->val))->value_).gc))))->cl.l))))->p;
  int counthook;

  int oldpc = (L->oldpc < p->sizecode) ? L->oldpc : 0;
  if (!(mask & ((1 << 2) | (1 << 3)))) {
    ci->u.l.trap = 0;
    return 0;
  }
  pc++;
  ci->u.l.savedpc = pc;
  counthook = (--L->hookcount == 0 && (mask & (1 << 3)));
  if (counthook)
    (L->hookcount = L->basehookcount);
  else if (!(mask & (1 << 2)))
    return 1;
  if (ci->callstatus & (1<<6)) {
    ci->callstatus &= ~(1<<6);
    return 1;
  }
  if (!((luaP_opmodes[(((OpCode)(((*(ci->u.l.savedpc - 1))>>0) & ((~((~(Instruction)0)<<(7)))<<(0)))))] & (1 << 5)) && ((((int)((((*(ci->u.l.savedpc - 1))>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0))))))) == 0))
    L->top = ci->top;
  if (counthook)
    luaD_hook(L, 3, -1, 0, 0);
  if (mask & (1 << 2)) {
    int npci = (((int)(((pc) - (p)->code))) - 1);
    if (npci == 0 ||
        pc <= ((p)->code + (oldpc) + 1) ||
        changedline(p, oldpc, npci)) {
      int newline = luaG_getfuncline(p, npci);
      luaD_hook(L, 2, newline, 0, 0);
    }
    L->oldpc = npci;
  }
  if (L->status == 1) {
    if (counthook)
      L->hookcount = 1;
    ci->u.l.savedpc--;
    ci->callstatus |= (1<<6);
    luaD_throw(L, 1);
  }
  return 1;
}
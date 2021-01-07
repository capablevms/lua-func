
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




static TValue *index2value (lua_State *L, int idx) {
  CallInfo *ci = L->ci;
  if (idx > 0) {
    StkId o = ci->func + idx;
    ((void)L, ((void)0));
    if (o >= L->top) return &(L->l_G)->nilvalue;
    else return (&(o)->val);
  }
  else if (!((idx) <= (-1000000 - 1000))) {
    ((void)L, ((void)0));
    return (&(L->top + idx)->val);
  }
  else if (idx == (-1000000 - 1000))
    return &(L->l_G)->l_registry;
  else {
    idx = (-1000000 - 1000) - idx;
    ((void)L, ((void)0));
    if ((((((&(ci->func)->val)))->tt_) == (((6) | ((1) << 4)))))
      return &(L->l_G)->nilvalue;
    else {
      CClosure *func = ((&((((union GCUnion *)(((((&(ci->func)->val))->value_).gc))))->cl.c)));
      return (idx <= func->nupvalues) ? &func->upvalue[idx-1] : &(L->l_G)->nilvalue;
    }
  }
}
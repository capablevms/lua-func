
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



extern const char * luaF_getlocalname(const Proto *, int, int);
extern int currentpc(CallInfo *);
extern const char * findvararg(CallInfo *, int, StkId *);

const char *luaG_findlocal (lua_State *L, CallInfo *ci, int n, StkId *pos) {
  StkId base = ci->func + 1;
  const char *name = ((void*)0);
  if ((!((ci)->callstatus & (1<<1)))) {
    if (n < 0)
      return findvararg(ci, n, pos);
    else
      name = luaF_getlocalname((((&((((union GCUnion *)(((((&((ci)->func)->val))->value_).gc))))->cl.l))))->p, n, currentpc(ci));
  }
  if (name == ((void*)0)) {
    StkId limit = (ci == L->ci) ? L->top : ci->next->func;
    if (limit - base >= n && n > 0) {

      name = (!((ci)->callstatus & (1<<1))) ? "(temporary)" : "(C temporary)";
    }
    else
      return ((void*)0);
  }
  if (pos)
    *pos = base + (n - 1);
  return name;
}
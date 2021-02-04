
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



extern const char * luaG_findlocal(lua_State *, CallInfo *, int, StkId *);
extern const char * luaF_getlocalname(const Proto *, int, int);

extern const char *lua_getlocal (lua_State *L, const lua_Debug *ar, int n) {
  const char *name;
  ((void) 0);
  if (ar == ((void*)0)) {
    if (!(((((&(L->top - 1)->val)))->tt_) == (((((6) | ((0) << 4))) | (1 << 6)))))
      name = ((void*)0);
    else
      name = luaF_getlocalname(((&((((union GCUnion *)(((((&(L->top - 1)->val))->value_).gc))))->cl.l)))->p, n, 0);
  }
  else {
    StkId pos = ((void*)0);
    name = luaG_findlocal(L, ar->i_ci, n, &pos);
    if (name) {
      { TValue *io1=((&(L->top)->val)); const TValue *io2=((&(pos)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
      {L->top++; ((void)L, ((void)0));};
    }
  }
  ((void) 0);
  return name;
}
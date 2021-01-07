
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



extern const char * aux_upvalue(TValue *, int, TValue **, GCObject **);
extern TValue * index2value(lua_State *, int);

extern const char *lua_getupvalue (lua_State *L, int funcindex, int n) {
  const char *name;
  TValue *val = ((void*)0);
  ((void) 0);
  name = aux_upvalue(index2value(L, funcindex), n, &val, ((void*)0));
  if (name) {
    { TValue *io1=((&(L->top)->val)); const TValue *io2=(val); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
    {L->top++; ((void)L, ((void)0));};
  }
  ((void) 0);
  return name;
}
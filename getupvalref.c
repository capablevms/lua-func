
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



extern TValue * index2value(lua_State *, int);

static UpVal **getupvalref (lua_State *L, int fidx, int n, LClosure **pf) {
  static const UpVal *const nullup = ((void*)0);
  LClosure *f;
  TValue *fi = index2value(L, fidx);
  ((void)L, ((void)0));
  f = ((&((((union GCUnion *)((((fi)->value_).gc))))->cl.l)));
  if (pf) *pf = f;
  if (1 <= n && n <= f->p->sizeupvalues)
    return &f->upvals[n - 1];
  else
    return (UpVal**)&nullup;
}
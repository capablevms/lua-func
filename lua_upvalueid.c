
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



extern UpVal ** getupvalref(lua_State *, int, int, LClosure **);
extern TValue * index2value(lua_State *, int);

extern void *lua_upvalueid (lua_State *L, int fidx, int n) {
  TValue *fi = index2value(L, fidx);
  switch (((((fi)->tt_)) & 0x3F)) {
    case ((6) | ((0) << 4)): {
      return *getupvalref(L, fidx, n, ((void*)0));
    }
    case ((6) | ((2) << 4)): {
      CClosure *f = ((&((((union GCUnion *)((((fi)->value_).gc))))->cl.c)));
      if (1 <= n && n <= f->nupvalues)
        return &f->upvalue[n - 1];

    }
    case ((6) | ((1) << 4)):
      return ((void*)0);
    default: {
      ((void)L, ((void)0));
      return ((void*)0);
    }
  }
}
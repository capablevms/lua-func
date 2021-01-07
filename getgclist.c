
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




static GCObject **getgclist (GCObject *o) {
  switch (o->tt) {
    case ((5) | ((0) << 4)): return &(&((((union GCUnion *)((o))))->h))->gclist;
    case ((6) | ((0) << 4)): return &(&((((union GCUnion *)((o))))->cl.l))->gclist;
    case ((6) | ((2) << 4)): return &(&((((union GCUnion *)((o))))->cl.c))->gclist;
    case ((8) | ((0) << 4)): return &(&((((union GCUnion *)((o))))->th))->gclist;
    case (((9 +1)) | ((0) << 4)): return &(&((((union GCUnion *)((o))))->p))->gclist;
    case ((7) | ((0) << 4)): {
      Udata *u = (&((((union GCUnion *)((o))))->u));
      ((void)0);
      return &u->gclist;
    }
    default: ((void)0); return 0;
  }
}
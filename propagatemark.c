
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



extern int traversethread(global_State *, lua_State *);
extern int traverseproto(global_State *, Proto *);
extern int traverseCclosure(global_State *, CClosure *);
extern int traverseLclosure(global_State *, LClosure *);
extern int traverseudata(global_State *, Udata *);
extern lu_mem traversetable(global_State *, Table *);
extern GCObject ** getgclist(GCObject *);

extern lu_mem propagatemark (global_State *g) {
  GCObject *o = g->gray;
  ((((o)->marked) |= ((1<<(5)))));
  g->gray = *getgclist(o);
  switch (o->tt) {
    case ((5) | ((0) << 4)): return traversetable(g, (&((((union GCUnion *)((o))))->h)));
    case ((7) | ((0) << 4)): return traverseudata(g, (&((((union GCUnion *)((o))))->u)));
    case ((6) | ((0) << 4)): return traverseLclosure(g, (&((((union GCUnion *)((o))))->cl.l)));
    case ((6) | ((2) << 4)): return traverseCclosure(g, (&((((union GCUnion *)((o))))->cl.c)));
    case (((9 +1)) | ((0) << 4)): return traverseproto(g, (&((((union GCUnion *)((o))))->p)));
    case ((8) | ((0) << 4)): return traversethread(g, (&((((union GCUnion *)((o))))->th)));
    default: ((void)0); return 0;
  }
}
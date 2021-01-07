
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



extern void correctpointers(global_State *, GCObject *);
extern GCObject ** sweeptolive(lua_State *, GCObject **);
extern const TValue * luaT_gettm(Table *, TMS, TString *);

void luaC_checkfinalizer (lua_State *L, GCObject *o, Table *mt) {
  global_State *g = (L->l_G);
  if ((((o)->marked) & ((1<<(6)))) ||
      ((mt) == ((void*)0) ? ((void*)0) : ((mt)->flags & (1u<<(TM_GC))) ? ((void*)0) : luaT_gettm(mt, TM_GC, (g)->tmname[TM_GC])) == ((void*)0))
    return;
  else {
    GCObject **p;
    if ((3 <= (g)->gcstate && (g)->gcstate <= 6)) {
      (o->marked = ((lu_byte)(((o->marked & ~((1<<(5)) | ((1<<(3)) | (1<<(4))))) | ((lu_byte)(((g)->currentwhite & ((1<<(3)) | (1<<(4))))))))));
      if (g->sweepgc == &o->next)
        g->sweepgc = sweeptolive(L, g->sweepgc);
    }
    else
      correctpointers(g, o);

    for (p = &g->allgc; *p != o; p = &(*p)->next) { }
    *p = o->next;
    o->next = g->finobj;
    g->finobj = o;
    ((o->marked) |= ((1<<(6))));
  }
}
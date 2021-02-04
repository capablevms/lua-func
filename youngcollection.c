
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



extern void finishgencycle(lua_State *, global_State *);
extern GCObject ** sweepgen(lua_State *, global_State *, GCObject **, GCObject *, GCObject **);
extern GCObject ** sweepgen(lua_State *, global_State *, GCObject **, GCObject *, GCObject **);
extern GCObject ** sweepgen(lua_State *, global_State *, GCObject **, GCObject *, GCObject **);
extern GCObject ** sweepgen(lua_State *, global_State *, GCObject **, GCObject *, GCObject **);
extern GCObject ** sweepgen(lua_State *, global_State *, GCObject **, GCObject *, GCObject **);
extern lu_mem atomic(lua_State *);
extern void markold(global_State *, GCObject *, GCObject *);
extern void markold(global_State *, GCObject *, GCObject *);
extern void markold(global_State *, GCObject *, GCObject *);

extern void youngcollection (lua_State *L, global_State *g) {
  GCObject **psurvival;
  GCObject *dummy;
  ((void)0);
  if (g->firstold1) {
    markold(g, g->firstold1, g->reallyold);
    g->firstold1 = ((void*)0);
  }
  markold(g, g->finobj, g->finobjrold);
  markold(g, g->tobefnz, ((void*)0));
  atomic(L);


  g->gcstate = 3;
  psurvival = sweepgen(L, g, &g->allgc, g->survival, &g->firstold1);

  sweepgen(L, g, psurvival, g->old1, &g->firstold1);
  g->reallyold = g->old1;
  g->old1 = *psurvival;
  g->survival = g->allgc;


  dummy = ((void*)0);
  psurvival = sweepgen(L, g, &g->finobj, g->finobjsur, &dummy);

  sweepgen(L, g, psurvival, g->finobjold1, &dummy);
  g->finobjrold = g->finobjold1;
  g->finobjold1 = *psurvival;
  g->finobjsur = g->finobj;

  sweepgen(L, g, &g->tobefnz, ((void*)0), &dummy);
  finishgencycle(L, g);
}
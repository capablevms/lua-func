
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



extern int runafewfinalizers(lua_State *, int);
extern void checkSizes(lua_State *, global_State *);
extern int sweepstep(lua_State *, global_State *, int, GCObject **);
extern int sweepstep(lua_State *, global_State *, int, GCObject **);
extern int sweepstep(lua_State *, global_State *, int, GCObject **);
extern void entersweep(lua_State *);
extern lu_mem atomic(lua_State *);
extern lu_mem propagatemark(global_State *);
extern void restartcollection(global_State *);

extern lu_mem singlestep (lua_State *L) {
  global_State *g = (L->l_G);
  switch (g->gcstate) {
    case 8: {
      restartcollection(g);
      g->gcstate = 0;
      return 1;
    }
    case 0: {
      if (g->gray == ((void*)0)) {
        g->gcstate = 1;
        return 0;
      }
      else
        return propagatemark(g);
    }
    case 1: {
      lu_mem work = atomic(L);
      entersweep(L);
      g->GCestimate = ((lu_mem)((g)->totalbytes + (g)->GCdebt)); ;
      return work;
    }
    case 3: {
      return sweepstep(L, g, 4, &g->finobj);
    }
    case 4: {
      return sweepstep(L, g, 5, &g->tobefnz);
    }
    case 5: {
      return sweepstep(L, g, 6, ((void*)0));
    }
    case 6: {
      checkSizes(L, g);
      g->gcstate = 7;
      return 0;
    }
    case 7: {
      if (g->tobefnz && !g->gcemergency) {
        int n = runafewfinalizers(L, 10);
        return n * 50;
      }
      else {
        g->gcstate = 8;
        return 0;
      }
    }
    default: ((void)0); return 0;
  }
}
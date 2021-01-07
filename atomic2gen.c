
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
extern void sweep2old(lua_State *, GCObject **);
extern void sweep2old(lua_State *, GCObject **);
extern void sweep2old(lua_State *, GCObject **);
extern void cleargraylists(global_State *);

static void atomic2gen (lua_State *L, global_State *g) {
  cleargraylists(g);

  g->gcstate = 3;
  sweep2old(L, &g->allgc);

  g->reallyold = g->old1 = g->survival = g->allgc;
  g->firstold1 = ((void*)0);


  sweep2old(L, &g->finobj);
  g->finobjrold = g->finobjold1 = g->finobjsur = g->finobj;

  sweep2old(L, &g->tobefnz);

  g->gckind = 1;
  g->lastatomic = 0;
  g->GCestimate = ((lu_mem)((g)->totalbytes + (g)->GCdebt));
  finishgencycle(L, g);
}
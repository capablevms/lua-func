
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



extern void close_state(lua_State *);
extern int luaD_rawrunprotected(lua_State *, Pfunc, void *);
extern unsigned int luai_makeseed(lua_State *);
extern void preinit_thread(lua_State *, global_State *);

extern lua_State *lua_newstate (lua_Alloc f, void *ud) {
  int i;
  lua_State *L;
  global_State *g;
  LG *l = ((LG *)((*f)(ud, ((void*)0), 8, sizeof(LG))));
  if (l == ((void*)0)) return ((void*)0);
  L = &l->l.l;
  g = &l->g;
  L->tt = ((8) | ((0) << 4));
  g->currentwhite = (1<<(3));
  L->marked = ((lu_byte)(((g)->currentwhite & ((1<<(3)) | (1<<(4))))));
  preinit_thread(L, g);
  g->allgc = (&(((union GCUnion *)((L)))->gc));
  L->next = ((void*)0);
  L->nCcalls = 0;
  ((L)->nCcalls += 0x10000);
  g->frealloc = f;
  g->ud = ud;
  g->warnf = ((void*)0);
  g->ud_warn = ((void*)0);
  g->mainthread = L;
  g->seed = luai_makeseed(L);
  g->gcrunning = 0;
  g->strt.size = g->strt.nuse = 0;
  g->strt.hash = ((void*)0);
  ((&g->l_registry)->tt_=(((0) | ((0) << 4))));
  g->panic = ((void*)0);
  g->gcstate = 8;
  g->gckind = 0;
  g->gcemergency = 0;
  g->finobj = g->tobefnz = g->fixedgc = ((void*)0);
  g->firstold1 = g->survival = g->old1 = g->reallyold = ((void*)0);
  g->finobjsur = g->finobjold1 = g->finobjrold = ((void*)0);
  g->sweepgc = ((void*)0);
  g->gray = g->grayagain = ((void*)0);
  g->weak = g->ephemeron = g->allweak = ((void*)0);
  g->twups = ((void*)0);
  g->totalbytes = sizeof(LG);
  g->GCdebt = 0;
  g->lastatomic = 0;
  { TValue *io=(&g->nilvalue); ((io)->value_).i=(0); ((io)->tt_=(((3) | ((0) << 4)))); };
  ((g->gcpause) = (200) / 4);
  ((g->gcstepmul) = (100) / 4);
  g->gcstepsize = 13;
  ((g->genmajormul) = (100) / 4);
  g->genminormul = 20;
  for (i=0; i < 9; i++) g->mt[i] = ((void*)0);
  if (luaD_rawrunprotected(L, f_luaopen, ((void*)0)) != 0) {

    close_state(L);
    L = ((void*)0);
  }
  return L;
}
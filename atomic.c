
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



extern void luaS_clearcache(global_State *);
extern void clearbyvalues(global_State *, GCObject *, GCObject *);
extern void clearbyvalues(global_State *, GCObject *, GCObject *);
extern void clearbykeys(global_State *, GCObject *);
extern void clearbykeys(global_State *, GCObject *);
extern void convergeephemerons(global_State *);
extern lu_mem propagateall(global_State *);
extern lu_mem markbeingfnz(global_State *);
extern void separatetobefnz(global_State *, int);
extern void clearbyvalues(global_State *, GCObject *, GCObject *);
extern void clearbyvalues(global_State *, GCObject *, GCObject *);
extern void convergeephemerons(global_State *);
extern lu_mem propagateall(global_State *);
extern lu_mem propagateall(global_State *);
extern int remarkupvals(global_State *);
extern lu_mem propagateall(global_State *);
extern void markmt(global_State *);
extern void reallymarkobject(global_State *, GCObject *);
extern void reallymarkobject(global_State *, GCObject *);

extern lu_mem atomic (lua_State *L) {
  global_State *g = (L->l_G);
  lu_mem work = 0;
  GCObject *origweak, *origall;
  GCObject *grayagain = g->grayagain;
  g->grayagain = ((void*)0);
  ((void)0);
  ((void)0);
  g->gcstate = 2;
  { if ((((L)->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g, (&(((union GCUnion *)((L)))->gc))); };

  { ((void)g->mainthread, ((void)0)); if (((((&g->l_registry)->tt_) & (1 << 6)) && ((((((&g->l_registry)->value_).gc))->marked) & (((1<<(3)) | (1<<(4))))))) reallymarkobject(g,(((&g->l_registry)->value_).gc)); };
  markmt(g);
  work += propagateall(g);

  work += remarkupvals(g);
  work += propagateall(g);
  g->gray = grayagain;
  work += propagateall(g);
  convergeephemerons(g);


  clearbyvalues(g, g->weak, ((void*)0));
  clearbyvalues(g, g->allweak, ((void*)0));
  origweak = g->weak; origall = g->allweak;
  separatetobefnz(g, 0);
  work += markbeingfnz(g);
  work += propagateall(g);
  convergeephemerons(g);


  clearbykeys(g, g->ephemeron);
  clearbykeys(g, g->allweak);

  clearbyvalues(g, g->weak, origweak);
  clearbyvalues(g, g->allweak, origall);
  luaS_clearcache(g);
  g->currentwhite = ((lu_byte)((((g)->currentwhite ^ ((1<<(3)) | (1<<(4)))))));
  ((void)0);
  return work;
}
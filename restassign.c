
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

struct LHS_assign {
  struct LHS_assign *prev;
  expdesc v;  /* variable (global, local, upvalue, or indexed) */
};

extern void luaK_storevar(FuncState *, expdesc *, expdesc *);
extern void init_exp(expdesc *, expkind, int);
extern void luaK_storevar(FuncState *, expdesc *, expdesc *);
extern void luaK_setoneret(FuncState *, expdesc *);
extern void adjust_assign(LexState *, int, int, expdesc *);
extern int explist(LexState *, expdesc *);
extern void checknext(LexState *, int);
extern void luaE_incCstack(lua_State *);
extern void check_conflict(LexState *, struct LHS_assign *, expdesc *);
extern void suffixedexp(LexState *, expdesc *);
extern int testnext(LexState *, int);
extern void check_readonly(LexState *, expdesc *);
extern void luaX_syntaxerror(LexState *, const char *);

extern void restassign (LexState *ls, struct LHS_assign *lh, int nvars) {
  expdesc e;
  { if (!((VLOCAL <= (lh->v.k) && (lh->v.k) <= VINDEXSTR))) luaX_syntaxerror(ls, "syntax error"); };
  check_readonly(ls, &lh->v);
  if (testnext(ls, ',')) {
    struct LHS_assign nv;
    nv.prev = lh;
    suffixedexp(ls, &nv.v);
    if (!(VINDEXED <= (nv.v.k) && (nv.v.k) <= VINDEXSTR))
      check_conflict(ls, lh, &nv.v);
    luaE_incCstack(ls->L);
    restassign(ls, &nv, nvars+1);
    ((ls)->L->nCcalls--);
  }
  else {
    int nexps;
    checknext(ls, '=');
    nexps = explist(ls, &e);
    if (nexps != nvars)
      adjust_assign(ls, nvars, nexps, &e);
    else {
      luaK_setoneret(ls->fs, &e);
      luaK_storevar(ls->fs, &lh->v, &e);
      return;
    }
  }
  init_exp(&e, VNONRELOC, ls->fs->freereg-1);
  luaK_storevar(ls->fs, &lh->v, &e);
}
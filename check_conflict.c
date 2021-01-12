
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

extern void luaK_reserveregs(FuncState *, int);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);

static void check_conflict (LexState *ls, struct LHS_assign *lh, expdesc *v) {
  FuncState *fs = ls->fs;
  int extra = fs->freereg;
  int conflict = 0;
  for (; lh; lh = lh->prev) {
    if ((VINDEXED <= (lh->v.k) && (lh->v.k) <= VINDEXSTR)) {
      if (lh->v.k == VINDEXUP) {
        if (v->k == VUPVAL && lh->v.u.ind.t == v->u.info) {
          conflict = 1;
          lh->v.k = VINDEXSTR;
          lh->v.u.ind.t = extra;
        }
      }
      else {
        if (v->k == VLOCAL && lh->v.u.ind.t == v->u.var.sidx) {
          conflict = 1;
          lh->v.u.ind.t = extra;
        }

        if (lh->v.k == VINDEXED && v->k == VLOCAL &&
            lh->v.u.ind.idx == v->u.var.sidx) {
          conflict = 1;
          lh->v.u.ind.idx = extra;
        }
      }
    }
  }
  if (conflict) {

    if (v->k == VLOCAL)
      luaK_codeABCk(fs,OP_MOVE,extra,v->u.var.sidx,0,0);
    else
      luaK_codeABCk(fs,OP_GETUPVAL,extra,v->u.info,0,0);
    luaK_reserveregs(fs, 1);
  }
}
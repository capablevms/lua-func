
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



extern int luaK_exp2anyreg(FuncState *, expdesc *);
extern int isCint(expdesc *);
extern int isKstr(FuncState *, expdesc *);
extern int luaK_exp2anyreg(FuncState *, expdesc *);
extern int isKstr(FuncState *, expdesc *);
extern void str2K(FuncState *, expdesc *);

void luaK_indexed (FuncState *fs, expdesc *t, expdesc *k) {
  if (k->k == VKSTR)
    str2K(fs, k);
  ((void)0);

  if (t->k == VUPVAL && !isKstr(fs, k))
    luaK_exp2anyreg(fs, t);
  if (t->k == VUPVAL) {
    t->u.ind.t = t->u.info;
    t->u.ind.idx = k->u.info;
    t->k = VINDEXUP;
  }
  else {

    t->u.ind.t = (t->k == VLOCAL) ? t->u.var.sidx: t->u.info;
    if (isKstr(fs, k)) {
      t->u.ind.idx = k->u.info;
      t->k = VINDEXSTR;
    }
    else if (isCint(k)) {
      t->u.ind.idx = ((int)((k->u.ival)));
      t->k = VINDEXI;
    }
    else {
      t->u.ind.idx = luaK_exp2anyreg(fs, k);
      t->k = VINDEXED;
    }
  }
}
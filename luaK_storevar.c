
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



extern void freeexp(FuncState *, expdesc *);
extern void codeABRK(FuncState *, OpCode, int, int, expdesc *);
extern void codeABRK(FuncState *, OpCode, int, int, expdesc *);
extern void codeABRK(FuncState *, OpCode, int, int, expdesc *);
extern void codeABRK(FuncState *, OpCode, int, int, expdesc *);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern int luaK_exp2anyreg(FuncState *, expdesc *);
extern void exp2reg(FuncState *, expdesc *, int);
extern void freeexp(FuncState *, expdesc *);

void luaK_storevar (FuncState *fs, expdesc *var, expdesc *ex) {
  switch (var->k) {
    case VLOCAL: {
      freeexp(fs, ex);
      exp2reg(fs, ex, var->u.var.sidx);
      return;
    }
    case VUPVAL: {
      int e = luaK_exp2anyreg(fs, ex);
      luaK_codeABCk(fs,OP_SETUPVAL,e,var->u.info,0,0);
      break;
    }
    case VINDEXUP: {
      codeABRK(fs, OP_SETTABUP, var->u.ind.t, var->u.ind.idx, ex);
      break;
    }
    case VINDEXI: {
      codeABRK(fs, OP_SETI, var->u.ind.t, var->u.ind.idx, ex);
      break;
    }
    case VINDEXSTR: {
      codeABRK(fs, OP_SETFIELD, var->u.ind.t, var->u.ind.idx, ex);
      break;
    }
    case VINDEXED: {
      codeABRK(fs, OP_SETTABLE, var->u.ind.t, var->u.ind.idx, ex);
      break;
    }
    default: ((void)0);
  }
  freeexp(fs, ex);
}
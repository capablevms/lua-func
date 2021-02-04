
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
extern int isSCnumber(expdesc *, int *, int *);
extern int luaK_exp2RK(FuncState *, expdesc *);
extern int tonumeral(const expdesc *, TValue *);
extern int luaK_exp2anyreg(FuncState *, expdesc *);
extern int tonumeral(const expdesc *, TValue *);
extern void luaK_exp2nextreg(FuncState *, expdesc *);
extern void luaK_goiffalse(FuncState *, expdesc *);
extern void luaK_goiftrue(FuncState *, expdesc *);
extern void luaK_dischargevars(FuncState *, expdesc *);

void luaK_infix (FuncState *fs, BinOpr op, expdesc *v) {
  luaK_dischargevars(fs, v);
  switch (op) {
    case OPR_AND: {
      luaK_goiftrue(fs, v);
      break;
    }
    case OPR_OR: {
      luaK_goiffalse(fs, v);
      break;
    }
    case OPR_CONCAT: {
      luaK_exp2nextreg(fs, v);
      break;
    }
    case OPR_ADD: case OPR_SUB:
    case OPR_MUL: case OPR_DIV: case OPR_IDIV:
    case OPR_MOD: case OPR_POW:
    case OPR_BAND: case OPR_BOR: case OPR_BXOR:
    case OPR_SHL: case OPR_SHR: {
      if (!tonumeral(v, ((void*)0)))
        luaK_exp2anyreg(fs, v);

      break;
    }
    case OPR_EQ: case OPR_NE: {
      if (!tonumeral(v, ((void*)0)))
        luaK_exp2RK(fs, v);

      break;
    }
    case OPR_LT: case OPR_LE:
    case OPR_GT: case OPR_GE: {
      int dummy, dummy2;
      if (!isSCnumber(v, &dummy, &dummy2))
        luaK_exp2anyreg(fs, v);

      break;
    }
    default: ((void)0);
  }
}
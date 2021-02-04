
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



extern void codeorder(FuncState *, OpCode, expdesc *, expdesc *);
extern void swapexps(expdesc *, expdesc *);
extern void codeorder(FuncState *, OpCode, expdesc *, expdesc *);
extern void codeeq(FuncState *, BinOpr, expdesc *, expdesc *);
extern void codebinexpval(FuncState *, OpCode, expdesc *, expdesc *, int);
extern void codebini(FuncState *, OpCode, expdesc *, expdesc *, int, int, TMS);
extern int isSCint(expdesc *);
extern void codebinexpval(FuncState *, OpCode, expdesc *, expdesc *, int);
extern int finishbinexpneg(FuncState *, expdesc *, expdesc *, OpCode, int, TMS);
extern void codebini(FuncState *, OpCode, expdesc *, expdesc *, int, int, TMS);
extern void swapexps(expdesc *, expdesc *);
extern int isSCint(expdesc *);
extern void codebitwise(FuncState *, BinOpr, expdesc *, expdesc *, int);
extern void codearith(FuncState *, BinOpr, expdesc *, expdesc *, int, int);
extern int finishbinexpneg(FuncState *, expdesc *, expdesc *, OpCode, int, TMS);
extern void codecommutative(FuncState *, BinOpr, expdesc *, expdesc *, int);
extern void codeconcat(FuncState *, expdesc *, expdesc *, int);
extern void luaK_exp2nextreg(FuncState *, expdesc *);
extern void luaK_concat(FuncState *, int *, int);
extern void luaK_concat(FuncState *, int *, int);
extern int constfolding(FuncState *, int, expdesc *, const expdesc *);
extern void luaK_dischargevars(FuncState *, expdesc *);

void luaK_posfix (FuncState *fs, BinOpr opr,
                  expdesc *e1, expdesc *e2, int line) {
  luaK_dischargevars(fs, e2);
  if (((opr) <= OPR_SHR) && constfolding(fs, opr + 0, e1, e2))
    return;
  switch (opr) {
    case OPR_AND: {
      ((void)0);
      luaK_concat(fs, &e2->f, e1->f);
      *e1 = *e2;
      break;
    }
    case OPR_OR: {
      ((void)0);
      luaK_concat(fs, &e2->t, e1->t);
      *e1 = *e2;
      break;
    }
    case OPR_CONCAT: {
      luaK_exp2nextreg(fs, e2);
      codeconcat(fs, e1, e2, line);
      break;
    }
    case OPR_ADD: case OPR_MUL: {
      codecommutative(fs, opr, e1, e2, line);
      break;
    }
    case OPR_SUB: {
      if (finishbinexpneg(fs, e1, e2, OP_ADDI, line, TM_SUB))
        break;

    }
    case OPR_DIV: case OPR_IDIV: case OPR_MOD: case OPR_POW: {
      codearith(fs, opr, e1, e2, 0, line);
      break;
    }
    case OPR_BAND: case OPR_BOR: case OPR_BXOR: {
      codebitwise(fs, opr, e1, e2, line);
      break;
    }
    case OPR_SHL: {
      if (isSCint(e1)) {
        swapexps(e1, e2);
        codebini(fs, OP_SHLI, e1, e2, 1, line, TM_SHL);
      }
      else if (finishbinexpneg(fs, e1, e2, OP_SHRI, line, TM_SHL)) {
                                 ;
      }
      else
       codebinexpval(fs, OP_SHL, e1, e2, line);
      break;
    }
    case OPR_SHR: {
      if (isSCint(e2))
        codebini(fs, OP_SHRI, e1, e2, 0, line, TM_SHR);
      else
        codebinexpval(fs, OP_SHR, e1, e2, line);
      break;
    }
    case OPR_EQ: case OPR_NE: {
      codeeq(fs, opr, e1, e2);
      break;
    }
    case OPR_LT: case OPR_LE: {
      OpCode op = ((OpCode)((opr - OPR_EQ) + OP_EQ));
      codeorder(fs, op, e1, e2);
      break;
    }
    case OPR_GT: case OPR_GE: {

      OpCode op = ((OpCode)((opr - OPR_NE) + OP_EQ));
      swapexps(e1, e2);
      codeorder(fs, op, e1, e2);
      break;
    }
    default: ((void)0);
  }
}
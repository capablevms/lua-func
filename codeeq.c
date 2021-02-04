
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



extern int condjump(FuncState *, OpCode, int, int, int, int);
extern void freeexps(FuncState *, expdesc *, expdesc *);
extern int luaK_exp2anyreg(FuncState *, expdesc *);
extern int luaK_exp2RK(FuncState *, expdesc *);
extern int isSCnumber(expdesc *, int *, int *);
extern int luaK_exp2anyreg(FuncState *, expdesc *);
extern void swapexps(expdesc *, expdesc *);

extern void codeeq (FuncState *fs, BinOpr opr, expdesc *e1, expdesc *e2) {
  int r1, r2;
  int im;
  int isfloat = 0;
  OpCode op;
  if (e1->k != VNONRELOC) {
    ((void)0);
    swapexps(e1, e2);
  }
  r1 = luaK_exp2anyreg(fs, e1);
  if (isSCnumber(e2, &im, &isfloat)) {
    op = OP_EQI;
    r2 = im;
  }
  else if (luaK_exp2RK(fs, e2)) {
    op = OP_EQK;
    r2 = e2->u.info;
  }
  else {
    op = OP_EQ;
    r2 = luaK_exp2anyreg(fs, e2);
  }
  freeexps(fs, e1, e2);
  e1->u.info = condjump(fs, op, r1, r2, isfloat, (opr == OPR_EQ));
  e1->k = VJMP;
}

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



extern void codearith(FuncState *, BinOpr, expdesc *, expdesc *, int, int);
extern void codebini(FuncState *, OpCode, expdesc *, expdesc *, int, int, TMS);
extern int isSCint(expdesc *);
extern void swapexps(expdesc *, expdesc *);
extern int tonumeral(const expdesc *, TValue *);

extern void codecommutative (FuncState *fs, BinOpr op,
                             expdesc *e1, expdesc *e2, int line) {
  int flip = 0;
  if (tonumeral(e1, ((void*)0))) {
    swapexps(e1, e2);
    flip = 1;
  }
  if (op == OPR_ADD && isSCint(e2))
    codebini(fs, ((OpCode)(OP_ADDI)), e1, e2, flip, line, TM_ADD);
  else
    codearith(fs, op, e1, e2, flip, line);
}
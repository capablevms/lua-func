
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



extern void codebinexpval(FuncState *, OpCode, expdesc *, expdesc *, int);
extern void swapexps(expdesc *, expdesc *);
extern void finishbinexpval(FuncState *, expdesc *, expdesc *, OpCode, int, int, int, OpCode, TMS);
extern int luaK_exp2K(FuncState *, expdesc *);
extern int tonumeral(const expdesc *, TValue *);

extern void codearith (FuncState *fs, BinOpr opr,
                       expdesc *e1, expdesc *e2, int flip, int line) {
  TMS event = ((TMS)(opr + TM_ADD));
  if (tonumeral(e2, ((void*)0)) && luaK_exp2K(fs, e2)) {
    int v2 = e2->u.info;
    OpCode op = ((OpCode)(opr + OP_ADDK));
    finishbinexpval(fs, e1, e2, op, v2, flip, line, OP_MMBINK, event);
  }
  else {
    OpCode op = ((OpCode)(opr + OP_ADD));
    if (flip)
      swapexps(e1, e2);
    codebinexpval(fs, op, e1, e2, line);
  }
}
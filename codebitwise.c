
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



extern void finishbinexpval(FuncState *, expdesc *, expdesc *, OpCode, int, int, int, OpCode, TMS);
extern void codebinexpval(FuncState *, OpCode, expdesc *, expdesc *, int);
extern int luaK_exp2RK(FuncState *, expdesc *);
extern void swapexps(expdesc *, expdesc *);
extern int luaK_exp2RK(FuncState *, expdesc *);

static void codebitwise (FuncState *fs, BinOpr opr,
                         expdesc *e1, expdesc *e2, int line) {
  int flip = 0;
  int v2;
  OpCode op;
  if (e1->k == VKINT && luaK_exp2RK(fs, e1)) {
    swapexps(e1, e2);
    flip = 1;
  }
  else if (!(e2->k == VKINT && luaK_exp2RK(fs, e2))) {
    op = ((OpCode)(opr + OP_ADD));
    codebinexpval(fs, op, e1, e2, line);
    return;
  }
  v2 = e2->u.info;
  op = ((OpCode)(opr + OP_ADDK));
  ((void)0);
  finishbinexpval(fs, e1, e2, op, v2, flip, line, OP_MMBINK,
                  ((TMS)(opr + TM_ADD)));
}
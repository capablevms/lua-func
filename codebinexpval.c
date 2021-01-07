
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
extern int luaK_exp2anyreg(FuncState *, expdesc *);

static void codebinexpval (FuncState *fs, OpCode op,
                           expdesc *e1, expdesc *e2, int line) {
  int v2 = luaK_exp2anyreg(fs, e2);
  ((void)0);
  finishbinexpval(fs, e1, e2, op, v2, 0, line, OP_MMBIN,
                  ((TMS)((op - OP_ADD) + TM_ADD)));
}
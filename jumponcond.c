
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
extern void freeexp(FuncState *, expdesc *);
extern void discharge2anyreg(FuncState *, expdesc *);
extern int condjump(FuncState *, OpCode, int, int, int, int);
extern void removelastinstruction(FuncState *);

static int jumponcond (FuncState *fs, expdesc *e, int cond) {
  if (e->k == VRELOC) {
    Instruction ie = ((fs)->f->code[(e)->u.info]);
    if ((((OpCode)(((ie)>>0) & ((~((~(Instruction)0)<<(7)))<<(0))))) == OP_NOT) {
      removelastinstruction(fs);
      return condjump(fs, OP_TEST, ((((int)((((ie)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0))))))), 0, 0, !cond);
    }

  }
  discharge2anyreg(fs, e);
  freeexp(fs, e);
  return condjump(fs, OP_TESTSET, ((1<<8)-1), e->u.info, 0, cond);
}
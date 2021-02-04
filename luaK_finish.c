
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



extern void fixjump(FuncState *, int, int);
extern int finaltarget(Instruction *, int);

void luaK_finish (FuncState *fs) {
  int i;
  Proto *p = fs->f;
  for (i = 0; i < fs->pc; i++) {
    Instruction *pc = &p->code[i];
    ((void)0);
    switch ((((OpCode)(((*pc)>>0) & ((~((~(Instruction)0)<<(7)))<<(0)))))) {
      case OP_RETURN0: case OP_RETURN1: {
        if (!(fs->needclose || p->is_vararg))
          break;

        ((*pc) = (((*pc)&(~((~((~(Instruction)0)<<(7)))<<(0)))) | ((((Instruction)(OP_RETURN))<<0)&((~((~(Instruction)0)<<(7)))<<(0)))));
      }
      case OP_RETURN: case OP_TAILCALL: {
        if (fs->needclose)
          ((*pc) = (((*pc)&(~((~((~(Instruction)0)<<(1)))<<(((0 + 7) + 8))))) | ((((Instruction)(1))<<((0 + 7) + 8))&((~((~(Instruction)0)<<(1)))<<(((0 + 7) + 8))))));
        if (p->is_vararg)
          ((*pc) = (((*pc)&(~((~((~(Instruction)0)<<(8)))<<(((((0 + 7) + 8) + 1) + 8))))) | ((((Instruction)(p->numparams + 1))<<((((0 + 7) + 8) + 1) + 8))&((~((~(Instruction)0)<<(8)))<<(((((0 + 7) + 8) + 1) + 8))))));
        break;
      }
      case OP_JMP: {
        int target = finaltarget(p->code, i);
        fixjump(fs, i, target);
        break;
      }
      default: break;
    }
  }
}
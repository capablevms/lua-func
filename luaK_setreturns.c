
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



extern void luaK_reserveregs(FuncState *, int);

void luaK_setreturns (FuncState *fs, expdesc *e, int nresults) {
  Instruction *pc = &((fs)->f->code[(e)->u.info]);
  if (e->k == VCALL)
    ((*pc) = (((*pc)&(~((~((~(Instruction)0)<<(8)))<<(((((0 + 7) + 8) + 1) + 8))))) | ((((Instruction)(nresults + 1))<<((((0 + 7) + 8) + 1) + 8))&((~((~(Instruction)0)<<(8)))<<(((((0 + 7) + 8) + 1) + 8))))));
  else {
    ((void)0);
    ((*pc) = (((*pc)&(~((~((~(Instruction)0)<<(8)))<<(((((0 + 7) + 8) + 1) + 8))))) | ((((Instruction)(nresults + 1))<<((((0 + 7) + 8) + 1) + 8))&((~((~(Instruction)0)<<(8)))<<(((((0 + 7) + 8) + 1) + 8))))));
    ((*pc) = (((*pc)&(~((~((~(Instruction)0)<<(8)))<<((0 + 7))))) | ((((Instruction)(fs->freereg))<<(0 + 7))&((~((~(Instruction)0)<<(8)))<<((0 + 7))))));
    luaK_reserveregs(fs, 1);
  }
}
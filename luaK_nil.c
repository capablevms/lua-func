
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



extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern Instruction * previousinstruction(FuncState *);

void luaK_nil (FuncState *fs, int from, int n) {
  int l = from + n - 1;
  Instruction *previous = previousinstruction(fs);
  if ((((OpCode)(((*previous)>>0) & ((~((~(Instruction)0)<<(7)))<<(0))))) == OP_LOADNIL) {
    int pfrom = (((int)((((*previous)>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0))))));
    int pl = pfrom + ((((int)((((*previous)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
    if ((pfrom <= from && from <= pl + 1) ||
        (from <= pfrom && pfrom <= l + 1)) {
      if (pfrom < from) from = pfrom;
      if (pl > l) l = pl;
      ((*previous) = (((*previous)&(~((~((~(Instruction)0)<<(8)))<<((0 + 7))))) | ((((Instruction)(from))<<(0 + 7))&((~((~(Instruction)0)<<(8)))<<((0 + 7))))));
      ((*previous) = (((*previous)&(~((~((~(Instruction)0)<<(8)))<<((((0 + 7) + 8) + 1))))) | ((((Instruction)(l - from))<<(((0 + 7) + 8) + 1))&((~((~(Instruction)0)<<(8)))<<((((0 + 7) + 8) + 1))))));
      return;
    }
  }
  luaK_codeABCk(fs,OP_LOADNIL,from,n - 1,0,0);
}
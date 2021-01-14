
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



extern Instruction * getjumpcontrol(FuncState *, int);

extern int patchtestreg (FuncState *fs, int node, int reg) {
  Instruction *i = getjumpcontrol(fs, node);
  if ((((OpCode)(((*i)>>0) & ((~((~(Instruction)0)<<(7)))<<(0))))) != OP_TESTSET)
    return 0;
  if (reg != ((1<<8)-1) && reg != ((((int)((((*i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0))))))))
    ((*i) = (((*i)&(~((~((~(Instruction)0)<<(8)))<<((0 + 7))))) | ((((Instruction)(reg))<<(0 + 7))&((~((~(Instruction)0)<<(8)))<<((0 + 7))))));
  else {


    *i = ((((Instruction)(OP_TEST))<<0) | (((Instruction)(((((int)((((*i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))<<(0 + 7)) | (((Instruction)(0))<<(((0 + 7) + 8) + 1)) | (((Instruction)(0))<<((((0 + 7) + 8) + 1) + 8)) | (((Instruction)(((((int)((((*i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<(1)))<<(0)))))))))<<((0 + 7) + 8)));
  }
  return 1;
}
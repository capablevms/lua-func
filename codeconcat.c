
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



extern void luaK_fixline(FuncState *, int);
extern void freeexp(FuncState *, expdesc *);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern void freeexp(FuncState *, expdesc *);
extern Instruction * previousinstruction(FuncState *);

static void codeconcat (FuncState *fs, expdesc *e1, expdesc *e2, int line) {
  Instruction *ie2 = previousinstruction(fs);
  if ((((OpCode)(((*ie2)>>0) & ((~((~(Instruction)0)<<(7)))<<(0))))) == OP_CONCAT) {
    int n = ((((int)((((*ie2)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
    ((void)0);
    freeexp(fs, e2);
    ((*ie2) = (((*ie2)&(~((~((~(Instruction)0)<<(8)))<<((0 + 7))))) | ((((Instruction)(e1->u.info))<<(0 + 7))&((~((~(Instruction)0)<<(8)))<<((0 + 7))))));
    ((*ie2) = (((*ie2)&(~((~((~(Instruction)0)<<(8)))<<((((0 + 7) + 8) + 1))))) | ((((Instruction)(n + 1))<<(((0 + 7) + 8) + 1))&((~((~(Instruction)0)<<(8)))<<((((0 + 7) + 8) + 1))))));
  }
  else {
    luaK_codeABCk(fs,OP_CONCAT,e1->u.info,2,0,0);
    freeexp(fs, e2);
    luaK_fixline(fs, line);
  }
}
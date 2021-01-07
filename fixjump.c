
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



extern void luaX_syntaxerror(LexState *, const char *);

static void fixjump (FuncState *fs, int pc, int dest) {
  Instruction *jmp = &fs->f->code[pc];
  int offset = dest - (pc + 1);
  ((void)0);
  if (!(-(((1 << ((8 + 8 + 1) + 8)) - 1) >> 1) <= offset && offset <= ((1 << ((8 + 8 + 1) + 8)) - 1) - (((1 << ((8 + 8 + 1) + 8)) - 1) >> 1)))
    luaX_syntaxerror(fs->ls, "control structure too long");
  ((void)0);
  ((*jmp) = (((*jmp)&(~((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<((0 + 7))))) | ((((Instruction)(((unsigned int)(((offset)+(((1 << ((8 + 8 + 1) + 8)) - 1) >> 1))))))<<(0 + 7))&((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<((0 + 7))))));
}
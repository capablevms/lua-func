
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



extern int luaO_ceillog2(unsigned int);

void luaK_settablesize (FuncState *fs, int pc, int ra, int asize, int hsize) {
  Instruction *inst = &fs->f->code[pc];
  int rb = (hsize != 0) ? luaO_ceillog2(hsize) + 1 : 0;
  int extra = asize / (((1<<8)-1) + 1);
  int rc = asize % (((1<<8)-1) + 1);
  int k = (extra > 0);
  *inst = ((((Instruction)(OP_NEWTABLE))<<0) | (((Instruction)(ra))<<(0 + 7)) | (((Instruction)(rb))<<(((0 + 7) + 8) + 1)) | (((Instruction)(rc))<<((((0 + 7) + 8) + 1) + 8)) | (((Instruction)(k))<<((0 + 7) + 8)));
  *(inst + 1) = ((((Instruction)(OP_EXTRAARG))<<0) | (((Instruction)(extra))<<(0 + 7)));
}
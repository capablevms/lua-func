
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



extern int luaK_code(FuncState *, Instruction);

int luaK_codeABCk (FuncState *fs, OpCode o, int a, int b, int c, int k) {
  ((void)0);
  ((void)0);

  return luaK_code(fs, ((((Instruction)(o))<<0) | (((Instruction)(a))<<(0 + 7)) | (((Instruction)(b))<<(((0 + 7) + 8) + 1)) | (((Instruction)(c))<<((((0 + 7) + 8) + 1) + 8)) | (((Instruction)(k))<<((0 + 7) + 8))));
}

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



extern void rname(const Proto *, int, int, const char **);
extern void kname(const Proto *, int, const char **);

static void rkname (const Proto *p, int pc, Instruction i, const char **name) {
  int c = ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
  if (((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<(1)))<<(0))))))))
    kname(p, c, name);
  else
    rname(p, pc, c, name);
}
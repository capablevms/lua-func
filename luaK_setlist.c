
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



extern int codeextraarg(FuncState *, int);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);

void luaK_setlist (FuncState *fs, int base, int nelems, int tostore) {
  ((void)0);
  if (tostore == (-1))
    tostore = 0;
  if (nelems <= ((1<<8)-1))
    luaK_codeABCk(fs,OP_SETLIST,base,tostore,nelems,0);
  else {
    int extra = nelems / (((1<<8)-1) + 1);
    nelems %= (((1<<8)-1) + 1);
    luaK_codeABCk(fs, OP_SETLIST, base, tostore, nelems, 1);
    codeextraarg(fs, extra);
  }
  fs->freereg = base + 1;
}
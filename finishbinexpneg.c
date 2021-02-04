
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



extern void finishbinexpval(FuncState *, expdesc *, expdesc *, OpCode, int, int, int, OpCode, TMS);
extern int fitsC(lua_Integer);
extern int fitsC(lua_Integer);
extern int luaK_isKint(expdesc *);

extern int finishbinexpneg (FuncState *fs, expdesc *e1, expdesc *e2,
                             OpCode op, int line, TMS event) {
  if (!luaK_isKint(e2))
    return 0;
  else {
    lua_Integer i2 = e2->u.ival;
    if (!(fitsC(i2) && fitsC(-i2)))
      return 0;
    else {
      int v2 = ((int)((i2)));
      finishbinexpval(fs, e1, e2, op, ((-v2) + (((1<<8)-1) >> 1)), 0, line, OP_MMBINI, event);

      ((fs->f->code[fs->pc - 1]) = (((fs->f->code[fs->pc - 1])&(~((~((~(Instruction)0)<<(8)))<<((((0 + 7) + 8) + 1))))) | ((((Instruction)(((v2) + (((1<<8)-1) >> 1))))<<(((0 + 7) + 8) + 1))&((~((~(Instruction)0)<<(8)))<<((((0 + 7) + 8) + 1))))));
      return 1;
    }
  }
}
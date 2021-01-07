
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



extern void freeexp(FuncState *, expdesc *);
extern void codeABRK(FuncState *, OpCode, int, int, expdesc *);
extern void luaK_reserveregs(FuncState *, int);
extern void freeexp(FuncState *, expdesc *);
extern int luaK_exp2anyreg(FuncState *, expdesc *);

void luaK_self (FuncState *fs, expdesc *e, expdesc *key) {
  int ereg;
  luaK_exp2anyreg(fs, e);
  ereg = e->u.info;
  freeexp(fs, e);
  e->u.info = fs->freereg;
  e->k = VNONRELOC;
  luaK_reserveregs(fs, 2);
  codeABRK(fs, OP_SELF, e->u.info, ereg, key);
  freeexp(fs, key);
}
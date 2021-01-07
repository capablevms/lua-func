
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
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern void freeexp(FuncState *, expdesc *);
extern int luaK_exp2anyreg(FuncState *, expdesc *);

static void codeunexpval (FuncState *fs, OpCode op, expdesc *e, int line) {
  int r = luaK_exp2anyreg(fs, e);
  freeexp(fs, e);
  e->u.info = luaK_codeABCk(fs,op,0,r,0,0);
  e->k = VRELOC;
  luaK_fixline(fs, line);
}
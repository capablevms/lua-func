
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



extern void luaK_exp2nextreg(FuncState *, expdesc *);
extern void exp2reg(FuncState *, expdesc *, int);
extern int luaY_nvarstack(FuncState *);
extern void luaK_dischargevars(FuncState *, expdesc *);

int luaK_exp2anyreg (FuncState *fs, expdesc *e) {
  luaK_dischargevars(fs, e);
  if (e->k == VNONRELOC) {
    if (!((e)->t != (e)->f))
      return e->u.info;
    if (e->u.info >= luaY_nvarstack(fs)) {
      exp2reg(fs, e, e->u.info);
      return e->u.info;
    }
  }
  luaK_exp2nextreg(fs, e);
  return e->u.info;
}
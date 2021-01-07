
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




void luaK_setoneret (FuncState *fs, expdesc *e) {
  if (e->k == VCALL) {

    ((void)0);
    e->k = VNONRELOC;
    e->u.info = (((int)((((((fs)->f->code[(e)->u.info]))>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0))))));
  }
  else if (e->k == VVARARG) {
    ((((fs)->f->code[(e)->u.info])) = (((((fs)->f->code[(e)->u.info]))&(~((~((~(Instruction)0)<<(8)))<<(((((0 + 7) + 8) + 1) + 8))))) | ((((Instruction)(2))<<((((0 + 7) + 8) + 1) + 8))&((~((~(Instruction)0)<<(8)))<<(((((0 + 7) + 8) + 1) + 8))))));
    e->k = VRELOC;
  }
}

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




static void const2exp (TValue *v, expdesc *e) {
  switch (((((v)->tt_)) & 0x3F)) {
    case ((3) | ((0) << 4)):
      e->k = VKINT; e->u.ival = (((v)->value_).i);
      break;
    case ((3) | ((1) << 4)):
      e->k = VKFLT; e->u.nval = (((v)->value_).n);
      break;
    case ((1) | ((0) << 4)):
      e->k = VFALSE;
      break;
    case ((1) | ((1) << 4)):
      e->k = VTRUE;
      break;
    case ((0) | ((0) << 4)):
      e->k = VNIL;
      break;
    case ((4) | ((0) << 4)): case ((4) | ((1) << 4)):
      e->k = VKSTR; e->u.strval = ((&((((union GCUnion *)((((v)->value_).gc))))->ts)));
      break;
    default: ((void)0);
  }
}
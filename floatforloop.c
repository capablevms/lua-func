
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

extern int floatforloop (StkId ra) {
  lua_Number step = ((((&(ra + 2)->val))->value_).n);
  lua_Number limit = ((((&(ra + 1)->val))->value_).n);
  lua_Number idx = ((((&(ra)->val))->value_).n);
  idx = ((idx)+(step));
  if (((0)<(step)) ? ((idx)<=(limit))
                          : ((limit)<=(idx))) {
    { TValue *io=((&(ra)->val)); ((void)0); ((io)->value_).n=(idx); };
    { TValue *io=((&(ra + 3)->val)); ((io)->value_).n=(idx); ((io)->tt_=(((3) | ((1) << 4)))); };
    return 1;
  }
  else
    return 0;
}

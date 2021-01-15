
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

int luaV_tointegerns (const TValue *obj, lua_Integer *p, F2Imod mode) {
  if (((((obj))->tt_) == (((3) | ((1) << 4)))))
    return luaV_flttointeger((((obj)->value_).n), p, mode);
  else if (((((obj))->tt_) == (((3) | ((0) << 4))))) {
    *p = (((obj)->value_).i);
    return 1;
  }
  else
    return 0;
}

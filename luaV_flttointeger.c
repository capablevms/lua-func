#include <math.h>

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

int luaV_flttointeger (lua_Number n, lua_Integer *p, F2Imod mode) {
  lua_Number f = (floor(n));
  if (n != f) {
    if (mode == F2Ieq) return 0;
    else if (mode == F2Iceil)
      f += 1;
  }
  return ((f) >= (double)((-9223372036854775807LL -1LL)) && (f) < -(double)((-9223372036854775807LL -1LL)) && (*(p) = (long long)(f), 1));
}

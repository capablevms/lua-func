
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

extern int l_strton (const TValue *, TValue *);

extern int luaV_tonumber_ (const TValue *obj, lua_Number *n) {
  TValue v;
  if (((((obj))->tt_) == (((3) | ((0) << 4))))) {
    *n = ((lua_Number)(((((obj)->value_).i))));
    return 1;
  }
  else if (l_strton(obj, &v)) {
    *n = ((((((&v))->tt_) == (((3) | ((0) << 4)))) ? ((lua_Number)(((((&v)->value_).i)))) : (((&v)->value_).n)));
    return 1;
  }
  else
    return 0;
}


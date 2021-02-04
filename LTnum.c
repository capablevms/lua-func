
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

extern int LTintfloat (lua_Integer, lua_Number);
extern int LTfloatint (lua_Number, lua_Integer);

extern int LTnum (const TValue *l, const TValue *r) {
  ((void)0);
  if (((((l))->tt_) == (((3) | ((0) << 4))))) {
    lua_Integer li = (((l)->value_).i);
    if (((((r))->tt_) == (((3) | ((0) << 4)))))
      return li < (((r)->value_).i);
    else
      return LTintfloat(li, (((r)->value_).n));
  }
  else {
    lua_Number lf = (((l)->value_).n);
    if (((((r))->tt_) == (((3) | ((1) << 4)))))
      return ((lf)<((((r)->value_).n)));
    else
      return LTfloatint(lf, (((r)->value_).i));
  }
}

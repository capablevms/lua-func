
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



extern const TValue * getgeneric(Table *, const TValue *, int);
extern const TValue * luaH_getint(Table *, lua_Integer);
extern int luaV_flttointeger(lua_Number, lua_Integer *, F2Imod);
extern const TValue * luaH_getint(Table *, lua_Integer);
extern const TValue * luaH_getshortstr(Table *, TString *);

const TValue *luaH_get (Table *t, const TValue *key) {
  switch (((((key)->tt_)) & 0x3F)) {
    case ((4) | ((0) << 4)): return luaH_getshortstr(t, ((&((((union GCUnion *)((((key)->value_).gc))))->ts))));
    case ((3) | ((0) << 4)): return luaH_getint(t, (((key)->value_).i));
    case ((0) | ((0) << 4)): return &absentkey;
    case ((3) | ((1) << 4)): {
      lua_Integer k;
      if (luaV_flttointeger((((key)->value_).n), &k, F2Ieq))
        return luaH_getint(t, k);

    }
    default:
      return getgeneric(t, key, 0);
  }
}

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



extern int luaV_tointegerns(const TValue *, lua_Integer *, F2Imod);
extern int luaV_tointegerns(const TValue *, lua_Integer *, F2Imod);

extern int validop (int op, TValue *v1, TValue *v2) {
  switch (op) {
    case 7: case 8: case 9:
    case 10: case 11: case 13: {
      lua_Integer i;
      return ((((((v1))->tt_) == (((3) | ((0) << 4)))) ? (*(&i) = (((v1)->value_).i), 1) : luaV_tointegerns(v1,&i,F2Ieq)) && (((((v2))->tt_) == (((3) | ((0) << 4)))) ? (*(&i) = (((v2)->value_).i), 1) : luaV_tointegerns(v2,&i,F2Ieq)));
    }
    case 5: case 6: case 3:
      return (((((((v2))->tt_) == (((3) | ((0) << 4)))) ? ((lua_Number)(((((v2)->value_).i)))) : (((v2)->value_).n))) != 0);
    default: return 1;
  }
}
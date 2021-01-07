
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



extern lua_Number numarith(lua_State *, int, lua_Number, lua_Number);
extern lua_Integer intarith(lua_State *, int, lua_Integer, lua_Integer);
extern lua_Number numarith(lua_State *, int, lua_Number, lua_Number);
extern lua_Integer intarith(lua_State *, int, lua_Integer, lua_Integer);
extern int luaV_tointegerns(const TValue *, lua_Integer *, F2Imod);
extern int luaV_tointegerns(const TValue *, lua_Integer *, F2Imod);

int luaO_rawarith (lua_State *L, int op, const TValue *p1, const TValue *p2,
                   TValue *res) {
  switch (op) {
    case 7: case 8: case 9:
    case 10: case 11:
    case 13: {
      lua_Integer i1; lua_Integer i2;
      if ((((((p1))->tt_) == (((3) | ((0) << 4)))) ? (*(&i1) = (((p1)->value_).i), 1) : luaV_tointegerns(p1,&i1,F2Ieq)) && (((((p2))->tt_) == (((3) | ((0) << 4)))) ? (*(&i2) = (((p2)->value_).i), 1) : luaV_tointegerns(p2,&i2,F2Ieq))) {
        { TValue *io=(res); ((io)->value_).i=(intarith(L, op, i1, i2)); ((io)->tt_=(((3) | ((0) << 4)))); };
        return 1;
      }
      else return 0;
    }
    case 5: case 4: {
      lua_Number n1; lua_Number n2;
      if ((((((p1))->tt_) == (((3) | ((1) << 4)))) ? ((n1) = (((p1)->value_).n), 1) : (((((p1))->tt_) == (((3) | ((0) << 4)))) ? ((n1) = ((lua_Number)(((((p1)->value_).i)))), 1) : 0)) && (((((p2))->tt_) == (((3) | ((1) << 4)))) ? ((n2) = (((p2)->value_).n), 1) : (((((p2))->tt_) == (((3) | ((0) << 4)))) ? ((n2) = ((lua_Number)(((((p2)->value_).i)))), 1) : 0))) {
        { TValue *io=(res); ((io)->value_).n=(numarith(L, op, n1, n2)); ((io)->tt_=(((3) | ((1) << 4)))); };
        return 1;
      }
      else return 0;
    }
    default: {
      lua_Number n1; lua_Number n2;
      if (((((p1))->tt_) == (((3) | ((0) << 4)))) && ((((p2))->tt_) == (((3) | ((0) << 4))))) {
        { TValue *io=(res); ((io)->value_).i=(intarith(L, op, (((p1)->value_).i), (((p2)->value_).i))); ((io)->tt_=(((3) | ((0) << 4)))); };
        return 1;
      }
      else if ((((((p1))->tt_) == (((3) | ((1) << 4)))) ? ((n1) = (((p1)->value_).n), 1) : (((((p1))->tt_) == (((3) | ((0) << 4)))) ? ((n1) = ((lua_Number)(((((p1)->value_).i)))), 1) : 0)) && (((((p2))->tt_) == (((3) | ((1) << 4)))) ? ((n2) = (((p2)->value_).n), 1) : (((((p2))->tt_) == (((3) | ((0) << 4)))) ? ((n2) = ((lua_Number)(((((p2)->value_).i)))), 1) : 0))) {
        { TValue *io=(res); ((io)->value_).n=(numarith(L, op, n1, n2)); ((io)->tt_=(((3) | ((1) << 4)))); };
        return 1;
      }
      else return 0;
    }
  }
}
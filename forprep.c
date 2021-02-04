
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

extern int forlimit (lua_State *, lua_Integer, const TValue *, lua_Integer *, lua_Integer);

extern int forprep (lua_State *L, StkId ra) {
  TValue *pinit = (&(ra)->val);
  TValue *plimit = (&(ra + 1)->val);
  TValue *pstep = (&(ra + 2)->val);
  if (((((pinit))->tt_) == (((3) | ((0) << 4)))) && ((((pstep))->tt_) == (((3) | ((0) << 4))))) {
    lua_Integer init = (((pinit)->value_).i);
    lua_Integer step = (((pstep)->value_).i);
    lua_Integer limit;
    if (step == 0)
      luaG_runerror(L, "'for' step is zero");
    { TValue *io=((&(ra + 3)->val)); ((io)->value_).i=(init); ((io)->tt_=(((3) | ((0) << 4)))); };
    if (forlimit(L, init, plimit, &limit, step))
      return 1;
    else {
      lua_Unsigned count;
      if (step > 0) {
        count = ((lua_Unsigned)(limit)) - ((lua_Unsigned)(init));
        if (step != 1)
          count /= ((lua_Unsigned)(step));
      }
      else {
        count = ((lua_Unsigned)(init)) - ((lua_Unsigned)(limit));

        count /= ((lua_Unsigned)(-(step + 1))) + 1u;
      }


      { TValue *io=(plimit); ((io)->value_).i=(((lua_Integer)(count))); ((io)->tt_=(((3) | ((0) << 4)))); };
    }
  }
  else {
    lua_Number init; lua_Number limit; lua_Number step;
    if ((__builtin_expect(((!(((((plimit))->tt_) == (((3) | ((1) << 4)))) ? (*(&limit) = (((plimit)->value_).n), 1) : luaV_tonumber_(plimit,&limit))) != 0), 0)))
      luaG_forerror(L, plimit, "limit");
    if ((__builtin_expect(((!(((((pstep))->tt_) == (((3) | ((1) << 4)))) ? (*(&step) = (((pstep)->value_).n), 1) : luaV_tonumber_(pstep,&step))) != 0), 0)))
      luaG_forerror(L, pstep, "step");
    if ((__builtin_expect(((!(((((pinit))->tt_) == (((3) | ((1) << 4)))) ? (*(&init) = (((pinit)->value_).n), 1) : luaV_tonumber_(pinit,&init))) != 0), 0)))
      luaG_forerror(L, pinit, "initial value");
    if (step == 0)
      luaG_runerror(L, "'for' step is zero");
    if (((0)<(step)) ? ((limit)<(init))
                            : ((init)<(limit)))
      return 1;
    else {

      { TValue *io=(plimit); ((io)->value_).n=(limit); ((io)->tt_=(((3) | ((1) << 4)))); };
      { TValue *io=(pstep); ((io)->value_).n=(step); ((io)->tt_=(((3) | ((1) << 4)))); };
      { TValue *io=((&(ra)->val)); ((io)->value_).n=(init); ((io)->tt_=(((3) | ((1) << 4)))); };
      { TValue *io=((&(ra + 3)->val)); ((io)->value_).n=(init); ((io)->tt_=(((3) | ((1) << 4)))); };
    }
  }
  return 0;
}


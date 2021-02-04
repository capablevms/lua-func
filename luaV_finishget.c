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

void luaV_finishget (lua_State *L, const TValue *t, TValue *key, StkId val,
                      const TValue *slot) {
  int loop;
  const TValue *tm;
  for (loop = 0; loop < 2000; loop++) {
    if (slot == ((void*)0)) {
      ((void)0);
      tm = luaT_gettmbyobj(L, t, TM_INDEX);
      if ((__builtin_expect((((((((((tm))->tt_)) & 0x0F)) == (0))) != 0), 0)))
        luaG_typeerror(L, t, "index");

    }
    else {
      ((void)0);
      tm = ((((&((((union GCUnion *)((((t)->value_).gc))))->h)))->metatable) == ((void*)0) ? ((void*)0) : ((((&((((union GCUnion *)((((t)->value_).gc))))->h)))->metatable)->flags & (1u<<(TM_INDEX))) ? ((void*)0) : luaT_gettm(((&((((union GCUnion *)((((t)->value_).gc))))->h)))->metatable, TM_INDEX, ((L->l_G))->tmname[TM_INDEX]));
      if (tm == ((void*)0)) {
        (((&(val)->val))->tt_=(((0) | ((0) << 4))));
        return;
      }

    }
    if (((((((tm)->tt_)) & 0x0F)) == (6))) {
      luaT_callTMres(L, tm, t, key, val);
      return;
    }
    t = tm;
    if ((!((((t))->tt_) == (((((5) | ((0) << 4))) | (1 << 6)))) ? (slot = ((void*)0), 0) : (slot = luaH_get(((&((((union GCUnion *)((((t)->value_).gc))))->h))), key), !(((((((slot))->tt_)) & 0x0F)) == (0))))) {
      { TValue *io1=((&(val)->val)); const TValue *io2=(slot); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
      return;
    }

  }
  luaG_runerror(L, "'__index' chain too long; possible loop");
}

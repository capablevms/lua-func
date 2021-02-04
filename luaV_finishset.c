
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

void luaV_finishset (lua_State *L, const TValue *t, TValue *key,
                     TValue *val, const TValue *slot) {
  int loop;
  for (loop = 0; loop < 2000; loop++) {
    const TValue *tm;
    if (slot != ((void*)0)) {
      Table *h = ((&((((union GCUnion *)((((t)->value_).gc))))->h)));
      ((void)0);
      tm = ((h->metatable) == ((void*)0) ? ((void*)0) : ((h->metatable)->flags & (1u<<(TM_NEWINDEX))) ? ((void*)0) : luaT_gettm(h->metatable, TM_NEWINDEX, ((L->l_G))->tmname[TM_NEWINDEX]));
      if (tm == ((void*)0)) {
        if (((((slot))->tt_) == (((0) | ((2) << 4)))))
          slot = luaH_newkey(L, h, key);

        { TValue *io1=(((TValue *)(slot))); const TValue *io2=(val); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
        ((h)->flags &= ~(~(~0u << (TM_EQ + 1))));
        ( ((((val)->tt_) & (1 << 6)) && ((((&(((union GCUnion *)((h)))->gc)))->marked) & ((1<<(5)))) && ((((((val)->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrierback_(L,(&(((union GCUnion *)((h)))->gc))) : ((void)((0))));
        return;
      }

    }
    else {
      tm = luaT_gettmbyobj(L, t, TM_NEWINDEX);
      if ((__builtin_expect((((((((((tm))->tt_)) & 0x0F)) == (0))) != 0), 0)))
        luaG_typeerror(L, t, "index");
    }

    if (((((((tm)->tt_)) & 0x0F)) == (6))) {
      luaT_callTM(L, tm, t, key, val);
      return;
    }
    t = tm;
    if ((!((((t))->tt_) == (((((5) | ((0) << 4))) | (1 << 6)))) ? (slot = ((void*)0), 0) : (slot = luaH_get(((&((((union GCUnion *)((((t)->value_).gc))))->h))), key), !(((((((slot))->tt_)) & 0x0F)) == (0))))) {
      { { TValue *io1=(((TValue *)(slot))); const TValue *io2=(val); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); }; ( ((((val)->tt_) & (1 << 6)) && ((((((t)->value_).gc))->marked) & ((1<<(5)))) && ((((((val)->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrierback_(L,(((t)->value_).gc)) : ((void)((0)))); };
      return;
    }

  }
  luaG_runerror(L, "'__newindex' chain too long; possible loop");
}

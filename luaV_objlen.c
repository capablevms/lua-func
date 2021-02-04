
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

void luaV_objlen (lua_State *L, StkId ra, const TValue *rb) {
  const TValue *tm;
  switch (((((rb)->tt_)) & 0x3F)) {
    case ((5) | ((0) << 4)): {
      Table *h = ((&((((union GCUnion *)((((rb)->value_).gc))))->h)));
      tm = ((h->metatable) == ((void*)0) ? ((void*)0) : ((h->metatable)->flags & (1u<<(TM_LEN))) ? ((void*)0) : luaT_gettm(h->metatable, TM_LEN, ((L->l_G))->tmname[TM_LEN]));
      if (tm) break;
      { TValue *io=((&(ra)->val)); ((io)->value_).i=(luaH_getn(h)); ((io)->tt_=(((3) | ((0) << 4)))); };
      return;
    }
    case ((4) | ((0) << 4)): {
      { TValue *io=((&(ra)->val)); ((io)->value_).i=(((&((((union GCUnion *)((((rb)->value_).gc))))->ts)))->shrlen); ((io)->tt_=(((3) | ((0) << 4)))); };
      return;
    }
    case ((4) | ((1) << 4)): {
      { TValue *io=((&(ra)->val)); ((io)->value_).i=(((&((((union GCUnion *)((((rb)->value_).gc))))->ts)))->u.lnglen); ((io)->tt_=(((3) | ((0) << 4)))); };
      return;
    }
    default: {
      tm = luaT_gettmbyobj(L, rb, TM_LEN);
      if ((__builtin_expect((((((((((tm))->tt_)) & 0x0F)) == (0))) != 0), 0)))
        luaG_typeerror(L, rb, "get length of");
      break;
    }
  }
  luaT_callTMres(L, tm, rb, rb, ra);
}

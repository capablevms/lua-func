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


extern int luaV_equalobj (lua_State *L, const TValue *t1, const TValue *t2) {
  const TValue *tm;
  if (((((t1)->tt_)) & 0x3F) != ((((t2)->tt_)) & 0x3F)) {
    if ((((((t1)->tt_)) & 0x0F)) != (((((t2)->tt_)) & 0x0F)) || (((((t1)->tt_)) & 0x0F)) != 3)
      return 0;
    else {
      lua_Integer i1, i2;
      return ((((((t1))->tt_) == (((3) | ((0) << 4)))) ? (*(&i1) = (((t1)->value_).i), 1) : luaV_tointegerns(t1,&i1,F2Ieq)) && (((((t2))->tt_) == (((3) | ((0) << 4)))) ? (*(&i2) = (((t2)->value_).i), 1) : luaV_tointegerns(t2,&i2,F2Ieq)) && i1 == i2);
    }
  }

  switch (((((t1)->tt_)) & 0x3F)) {
    case ((0) | ((0) << 4)): case ((1) | ((0) << 4)): case ((1) | ((1) << 4)): return 1;
    case ((3) | ((0) << 4)): return ((((t1)->value_).i) == (((t2)->value_).i));
    case ((3) | ((1) << 4)): return (((((t1)->value_).n))==((((t2)->value_).n)));
    case ((2) | ((0) << 4)): return (((t1)->value_).p) == (((t2)->value_).p);
    case ((6) | ((1) << 4)): return (((t1)->value_).f) == (((t2)->value_).f);
    case ((4) | ((0) << 4)): return ((((&((((union GCUnion *)((((t1)->value_).gc))))->ts)))) == (((&((((union GCUnion *)((((t2)->value_).gc))))->ts)))));
    case ((4) | ((1) << 4)): return luaS_eqlngstr(((&((((union GCUnion *)((((t1)->value_).gc))))->ts))), ((&((((union GCUnion *)((((t2)->value_).gc))))->ts))));
    case ((7) | ((0) << 4)): {
      if (((&((((union GCUnion *)((((t1)->value_).gc))))->u))) == ((&((((union GCUnion *)((((t2)->value_).gc))))->u)))) return 1;
      else if (L == ((void*)0)) return 0;
      tm = ((((&((((union GCUnion *)((((t1)->value_).gc))))->u)))->metatable) == ((void*)0) ? ((void*)0) : ((((&((((union GCUnion *)((((t1)->value_).gc))))->u)))->metatable)->flags & (1u<<(TM_EQ))) ? ((void*)0) : luaT_gettm(((&((((union GCUnion *)((((t1)->value_).gc))))->u)))->metatable, TM_EQ, ((L->l_G))->tmname[TM_EQ]));
      if (tm == ((void*)0))
        tm = ((((&((((union GCUnion *)((((t2)->value_).gc))))->u)))->metatable) == ((void*)0) ? ((void*)0) : ((((&((((union GCUnion *)((((t2)->value_).gc))))->u)))->metatable)->flags & (1u<<(TM_EQ))) ? ((void*)0) : luaT_gettm(((&((((union GCUnion *)((((t2)->value_).gc))))->u)))->metatable, TM_EQ, ((L->l_G))->tmname[TM_EQ]));
      break;
    }
    case ((5) | ((0) << 4)): {
      if (((&((((union GCUnion *)((((t1)->value_).gc))))->h))) == ((&((((union GCUnion *)((((t2)->value_).gc))))->h)))) return 1;
      else if (L == ((void*)0)) return 0;
      tm = ((((&((((union GCUnion *)((((t1)->value_).gc))))->h)))->metatable) == ((void*)0) ? ((void*)0) : ((((&((((union GCUnion *)((((t1)->value_).gc))))->h)))->metatable)->flags & (1u<<(TM_EQ))) ? ((void*)0) : luaT_gettm(((&((((union GCUnion *)((((t1)->value_).gc))))->h)))->metatable, TM_EQ, ((L->l_G))->tmname[TM_EQ]));
      if (tm == ((void*)0))
        tm = ((((&((((union GCUnion *)((((t2)->value_).gc))))->h)))->metatable) == ((void*)0) ? ((void*)0) : ((((&((((union GCUnion *)((((t2)->value_).gc))))->h)))->metatable)->flags & (1u<<(TM_EQ))) ? ((void*)0) : luaT_gettm(((&((((union GCUnion *)((((t2)->value_).gc))))->h)))->metatable, TM_EQ, ((L->l_G))->tmname[TM_EQ]));
      break;
    }
    default:
      return (((t1)->value_).gc) == (((t2)->value_).gc);
  }
  if (tm == ((void*)0))
    return 0;
  else {
    luaT_callTMres(L, tm, t1, t2, L->top);
    return !((((((&(L->top)->val)))->tt_) == (((1) | ((0) << 4)))) || ((((((((&(L->top)->val)))->tt_)) & 0x0F)) == (0)));
  }
}

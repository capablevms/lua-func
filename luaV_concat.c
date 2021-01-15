#include <string.h>

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

static void copy2buff (StkId top, int n, char *buff) {
  size_t tl = 0;
  do {
    size_t l = ((((&((((union GCUnion *)(((((&(top - n)->val))->value_).gc))))->ts))))->tt == ((4) | ((0) << 4)) ? (((&((((union GCUnion *)(((((&(top - n)->val))->value_).gc))))->ts))))->shrlen : (((&((((union GCUnion *)(((((&(top - n)->val))->value_).gc))))->ts))))->u.lnglen);
    memcpy(buff + tl, ((((&((((union GCUnion *)(((((&(top - n)->val))->value_).gc))))->ts))))->contents), l * sizeof(char));
    tl += l;
  } while (--n > 0);
}

void luaV_concat (lua_State *L, int total) {
  if (total == 1)
    return;
  do {
    StkId top = L->top;
    int n = 2;
    if (!(((((((((&(top - 2)->val)))->tt_)) & 0x0F)) == (4)) || ((((((((&(top - 2)->val)))->tt_)) & 0x0F)) == (3))) ||
        !(((((((((&(top - 1)->val)))->tt_)) & 0x0F)) == (4)) || (((((((((&(top - 1)->val)))->tt_)) & 0x0F)) == (3)) && (luaO_tostring(L, (&(top - 1)->val)), 1))))
      luaT_tryconcatTM(L);
    else if (((((((&(top - 1)->val)))->tt_) == (((((4) | ((0) << 4))) | (1 << 6)))) && ((&((((union GCUnion *)(((((&(top - 1)->val))->value_).gc))))->ts)))->shrlen == 0))
      ((void)(((((((((((&(top - 2)->val)))->tt_)) & 0x0F)) == (4)) || (((((((((&(top - 2)->val)))->tt_)) & 0x0F)) == (3)) && (luaO_tostring(L, (&(top - 2)->val)), 1))))));
    else if (((((((&(top - 2)->val)))->tt_) == (((((4) | ((0) << 4))) | (1 << 6)))) && ((&((((union GCUnion *)(((((&(top - 2)->val))->value_).gc))))->ts)))->shrlen == 0)) {
      { TValue *io1=((&(top - 2)->val)); const TValue *io2=((&(top - 1)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
    }
    else {

      size_t tl = ((((&((((union GCUnion *)(((((&(top - 1)->val))->value_).gc))))->ts))))->tt == ((4) | ((0) << 4)) ? (((&((((union GCUnion *)(((((&(top - 1)->val))->value_).gc))))->ts))))->shrlen : (((&((((union GCUnion *)(((((&(top - 1)->val))->value_).gc))))->ts))))->u.lnglen);
      TString *ts;

      for (n = 1; n < total && (((((((((&(top - n - 1)->val)))->tt_)) & 0x0F)) == (4)) || (((((((((&(top - n - 1)->val)))->tt_)) & 0x0F)) == (3)) && (luaO_tostring(L, (&(top - n - 1)->val)), 1))); n++) {
        size_t l = ((((&((((union GCUnion *)(((((&(top - n - 1)->val))->value_).gc))))->ts))))->tt == ((4) | ((0) << 4)) ? (((&((((union GCUnion *)(((((&(top - n - 1)->val))->value_).gc))))->ts))))->shrlen : (((&((((union GCUnion *)(((((&(top - n - 1)->val))->value_).gc))))->ts))))->u.lnglen);
        if ((__builtin_expect(((l >= ((sizeof(size_t) < sizeof(lua_Integer) ? ((size_t)(~(size_t)0)) : (size_t)(9223372036854775807LL))/sizeof(char)) - tl) != 0), 0)))
          luaG_runerror(L, "string length overflow");
        tl += l;
      }
      if (tl <= 40) {
        char buff[40];
        copy2buff(top, n, buff);
        ts = luaS_newlstr(L, buff, tl);
      }
      else {
        ts = luaS_createlngstrobj(L, tl);
        copy2buff(top, n, ((ts)->contents));
      }
      { TValue *io = ((&(top - n)->val)); TString *x_ = (ts); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((x_->tt) | (1 << 6)))); ((void)L, ((void)0)); };
    }
    total -= n-1;
    L->top -= n-1;
  } while (total > 1);
}

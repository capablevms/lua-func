
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



extern TString * luaS_newlstr(lua_State *, const char *, size_t);

void luaD_seterrorobj (lua_State *L, int errcode, StkId oldtop) {
  switch (errcode) {
    case 4: {
      { TValue *io = ((&(oldtop)->val)); TString *x_ = ((L->l_G)->memerrmsg); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((x_->tt) | (1 << 6)))); ((void)L, ((void)0)); };
      break;
    }
    case 5: {
      { TValue *io = ((&(oldtop)->val)); TString *x_ = ((luaS_newlstr(L, "" "error in error handling", (sizeof("error in error handling")/sizeof(char))-1))); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((x_->tt) | (1 << 6)))); ((void)L, ((void)0)); };
      break;
    }
    case (-2): {
      (((&(oldtop)->val))->tt_=(((0) | ((0) << 4))));
      break;
    }
    default: {
      { TValue *io1=((&(oldtop)->val)); const TValue *io2=((&(L->top - 1)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
      break;
    }
  }
  L->top = oldtop + 1;
}
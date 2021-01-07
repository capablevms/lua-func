
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



extern int tonumeral(const expdesc *, TValue *);
extern TValue * const2val(FuncState *, const expdesc *);

int luaK_exp2const (FuncState *fs, const expdesc *e, TValue *v) {
  if (((e)->t != (e)->f))
    return 0;
  switch (e->k) {
    case VFALSE:
      ((v)->tt_=(((1) | ((0) << 4))));
      return 1;
    case VTRUE:
      ((v)->tt_=(((1) | ((1) << 4))));
      return 1;
    case VNIL:
      ((v)->tt_=(((0) | ((0) << 4))));
      return 1;
    case VKSTR: {
      { TValue *io = (v); TString *x_ = (e->u.strval); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((x_->tt) | (1 << 6)))); ((void)fs->ls->L, ((void)0)); };
      return 1;
    }
    case VCONST: {
      { TValue *io1=(v); const TValue *io2=(const2val(fs, e)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)fs->ls->L, ((void)0)); ((void)0); };
      return 1;
    }
    default: return tonumeral(e, v);
  }
}
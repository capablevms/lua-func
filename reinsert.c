
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



extern TValue * luaH_set(lua_State *, Table *, const TValue *);

static void reinsert (lua_State *L, Table *ot, Table *t) {
  int j;
  int size = ((1<<((ot)->lsizenode)));
  for (j = 0; j < size; j++) {
    Node *old = (&(ot)->node[j]);
    if (!((((((((&(old)->i_val)))->tt_)) & 0x0F)) == (0))) {


      TValue k;
      { TValue *io_=(&k); const Node *n_=(old); io_->value_ = n_->u.key_val; io_->tt_ = n_->u.key_tt; ((void)L, ((void)0)); };
      { TValue *io1=(luaH_set(L, t, &k)); const TValue *io2=((&(old)->i_val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
    }
  }
}
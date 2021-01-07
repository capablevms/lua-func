
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



extern unsigned int findindex(lua_State *, Table *, TValue *, unsigned int);
extern unsigned int luaH_realasize(const Table *);

int luaH_next (lua_State *L, Table *t, StkId key) {
  unsigned int asize = luaH_realasize(t);
  unsigned int i = findindex(L, t, (&(key)->val), asize);
  for (; i < asize; i++) {
    if (!(((((((&t->array[i]))->tt_)) & 0x0F)) == (0))) {
      { TValue *io=((&(key)->val)); ((io)->value_).i=(i + 1); ((io)->tt_=(((3) | ((0) << 4)))); };
      { TValue *io1=((&(key + 1)->val)); const TValue *io2=(&t->array[i]); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
      return 1;
    }
  }
  for (i -= asize; ((int)((i))) < ((1<<((t)->lsizenode))); i++) {
    if (!((((((((&((&(t)->node[i]))->i_val)))->tt_)) & 0x0F)) == (0))) {
      Node *n = (&(t)->node[i]);
      { TValue *io_=((&(key)->val)); const Node *n_=(n); io_->value_ = n_->u.key_val; io_->tt_ = n_->u.key_tt; ((void)L, ((void)0)); };
      { TValue *io1=((&(key + 1)->val)); const TValue *io2=((&(n)->i_val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
      return 1;
    }
  }
  return 0;
}
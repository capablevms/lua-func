
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



extern const TValue * getgeneric(Table *, const TValue *, int);
extern const TValue * luaH_getshortstr(Table *, TString *);

const TValue *luaH_getstr (Table *t, TString *key) {
  if (key->tt == ((4) | ((0) << 4)))
    return luaH_getshortstr(t, key);
  else {
    TValue ko;
    { TValue *io = (&ko); TString *x_ = (key); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((x_->tt) | (1 << 6)))); ((void)((lua_State *)(((void*)0))), ((void)0)); };
    return getgeneric(t, &ko, 0);
  }
}
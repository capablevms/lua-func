
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




const TValue *luaH_getshortstr (Table *t, TString *key) {
  Node *n = ((&(t)->node[(((((int)(((((key)->hash)) & ((((1<<((t)->lsizenode))))-1)))))))]));
  ((void)0);
  for (;;) {
    if ((((n)->u.key_tt) == ((((4) | ((0) << 4))) | (1 << 6))) && ((((&((((union GCUnion *)((((n)->u.key_val).gc))))->ts)))) == (key)))
      return (&(n)->i_val);
    else {
      int nx = ((n)->u.next);
      if (nx == 0)
        return &absentkey;
      n += nx;
    }
  }
}
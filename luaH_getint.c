
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



extern unsigned int luaH_realasize(const Table *);

const TValue *luaH_getint (Table *t, lua_Integer key) {
  if (((lua_Unsigned)(key)) - 1u < t->alimit)
    return &t->array[key - 1];
  else if (!((!((t)->flags & (1 << 7))) || ((((t)->alimit) & (((t)->alimit) - 1)) == 0)) &&
           (((lua_Unsigned)(key)) == t->alimit + 1 ||
            ((lua_Unsigned)(key)) - 1u < luaH_realasize(t))) {
    t->alimit = ((unsigned int)((key)));
    return &t->array[key - 1];
  }
  else {
    Node *n = ((&(t)->node[(((((int)((((key)) & ((((1<<((t)->lsizenode))))-1)))))))]));
    for (;;) {
      if ((((n)->u.key_tt) == ((3) | ((0) << 4))) && (((n)->u.key_val).i) == key)
        return (&(n)->i_val);
      else {
        int nx = ((n)->u.next);
        if (nx == 0) break;
        n += nx;
      }
    }
    return &absentkey;
  }
}
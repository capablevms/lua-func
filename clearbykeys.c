
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



extern void clearkey(Node *);
extern int iscleared(global_State *, const GCObject *);

static void clearbykeys (global_State *g, GCObject *l) {
  for (; l; l = (&((((union GCUnion *)((l))))->h))->gclist) {
    Table *h = (&((((union GCUnion *)((l))))->h));
    Node *limit = (&(h)->node[((size_t)((((1<<((h)->lsizenode))))))]);
    Node *n;
    for (n = (&(h)->node[0]); n < limit; n++) {
      if (iscleared(g, ((((n)->u.key_tt) & (1 << 6)) ? (((n)->u.key_val).gc) : ((void*)0))))
        (((&(n)->i_val))->tt_=(((0) | ((1) << 4))));
      if (((((((((&(n)->i_val)))->tt_)) & 0x0F)) == (0)))
        clearkey(n);
    }
  }
}
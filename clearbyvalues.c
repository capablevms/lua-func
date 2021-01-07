
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
extern int iscleared(global_State *, const GCObject *);
extern unsigned int luaH_realasize(const Table *);

static void clearbyvalues (global_State *g, GCObject *l, GCObject *f) {
  for (; l != f; l = (&((((union GCUnion *)((l))))->h))->gclist) {
    Table *h = (&((((union GCUnion *)((l))))->h));
    Node *n, *limit = (&(h)->node[((size_t)((((1<<((h)->lsizenode))))))]);
    unsigned int i;
    unsigned int asize = luaH_realasize(h);
    for (i = 0; i < asize; i++) {
      TValue *o = &h->array[i];
      if (iscleared(g, ((((o)->tt_) & (1 << 6)) ? (((o)->value_).gc) : ((void*)0))))
        ((o)->tt_=(((0) | ((1) << 4))));
    }
    for (n = (&(h)->node[0]); n < limit; n++) {
      if (iscleared(g, (((((&(n)->i_val))->tt_) & (1 << 6)) ? ((((&(n)->i_val))->value_).gc) : ((void*)0))))
        (((&(n)->i_val))->tt_=(((0) | ((1) << 4))));
      if (((((((((&(n)->i_val)))->tt_)) & 0x0F)) == (0)))
        clearkey(n);
    }
  }
}
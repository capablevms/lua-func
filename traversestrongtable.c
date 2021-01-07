
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



extern void genlink(global_State *, GCObject *);
extern void reallymarkobject(global_State *, GCObject *);
extern void reallymarkobject(global_State *, GCObject *);
extern void clearkey(Node *);
extern void reallymarkobject(global_State *, GCObject *);
extern unsigned int luaH_realasize(const Table *);

static void traversestrongtable (global_State *g, Table *h) {
  Node *n, *limit = (&(h)->node[((size_t)((((1<<((h)->lsizenode))))))]);
  unsigned int i;
  unsigned int asize = luaH_realasize(h);
  for (i = 0; i < asize; i++)
    { ((void)g->mainthread, ((void)0)); if (((((&h->array[i])->tt_) & (1 << 6)) && ((((((&h->array[i])->value_).gc))->marked) & (((1<<(3)) | (1<<(4))))))) reallymarkobject(g,(((&h->array[i])->value_).gc)); };
  for (n = (&(h)->node[0]); n < limit; n++) {
    if (((((((((&(n)->i_val)))->tt_)) & 0x0F)) == (0)))
      clearkey(n);
    else {
      ((void)0);
      { if ((((n)->u.key_tt) & (1 << 6)) && ((((((n)->u.key_val).gc))->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g,(((n)->u.key_val).gc)); };
      { ((void)g->mainthread, ((void)0)); if ((((((&(n)->i_val))->tt_) & (1 << 6)) && (((((((&(n)->i_val))->value_).gc))->marked) & (((1<<(3)) | (1<<(4))))))) reallymarkobject(g,((((&(n)->i_val))->value_).gc)); };
    }
  }
  genlink(g, (&(((union GCUnion *)((h)))->gc)));
}
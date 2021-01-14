
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
extern void linkgclist_(GCObject *, GCObject **, GCObject **);
extern void linkgclist_(GCObject *, GCObject **, GCObject **);
extern void linkgclist_(GCObject *, GCObject **, GCObject **);
extern void reallymarkobject(global_State *, GCObject *);
extern int iscleared(global_State *, const GCObject *);
extern void clearkey(Node *);
extern void reallymarkobject(global_State *, GCObject *);
extern unsigned int luaH_realasize(const Table *);

extern int traverseephemeron (global_State *g, Table *h, int inv) {
  int marked = 0;
  int hasclears = 0;
  int hasww = 0;
  unsigned int i;
  unsigned int asize = luaH_realasize(h);
  unsigned int nsize = ((1<<((h)->lsizenode)));

  for (i = 0; i < asize; i++) {
    if (((((&h->array[i])->tt_) & (1 << 6)) && ((((((&h->array[i])->value_).gc))->marked) & (((1<<(3)) | (1<<(4))))))) {
      marked = 1;
      reallymarkobject(g, (((&h->array[i])->value_).gc));
    }
  }


  for (i = 0; i < nsize; i++) {
    Node *n = inv ? (&(h)->node[nsize - 1 - i]) : (&(h)->node[i]);
    if (((((((((&(n)->i_val)))->tt_)) & 0x0F)) == (0)))
      clearkey(n);
    else if (iscleared(g, ((((n)->u.key_tt) & (1 << 6)) ? (((n)->u.key_val).gc) : ((void*)0)))) {
      hasclears = 1;
      if ((((((&(n)->i_val))->tt_) & (1 << 6)) && (((((((&(n)->i_val))->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))))
        hasww = 1;
    }
    else if ((((((&(n)->i_val))->tt_) & (1 << 6)) && (((((((&(n)->i_val))->value_).gc))->marked) & (((1<<(3)) | (1<<(4))))))) {
      marked = 1;
      reallymarkobject(g, ((((&(n)->i_val))->value_).gc));
    }
  }

  if (g->gcstate == 0)
    linkgclist_((&(((union GCUnion *)((h)))->gc)), &(h)->gclist, &(g->grayagain));
  else if (hasww)
    linkgclist_((&(((union GCUnion *)((h)))->gc)), &(h)->gclist, &(g->ephemeron));
  else if (hasclears)
    linkgclist_((&(((union GCUnion *)((h)))->gc)), &(h)->gclist, &(g->allweak));
  else
    genlink(g, (&(((union GCUnion *)((h)))->gc)));
  return marked;
}
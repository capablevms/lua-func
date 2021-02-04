
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



extern void linkgclist_(GCObject *, GCObject **, GCObject **);
extern void freeobj(lua_State *, GCObject *);

extern void sweep2old (lua_State *L, GCObject **p) {
  GCObject *curr;
  global_State *g = (L->l_G);
  while ((curr = *p) != ((void*)0)) {
    if ((((curr)->marked) & (((1<<(3)) | (1<<(4)))))) {
      ((void)0);
      *p = curr->next;
      freeobj(L, curr);
    }
    else {
      ((curr)->marked = ((lu_byte)((((curr)->marked & (~7)) | 4))));
      if (curr->tt == ((8) | ((0) << 4))) {
        lua_State *th = (&((((union GCUnion *)((curr))))->th));
        linkgclist_((&(((union GCUnion *)((th)))->gc)), &(th)->gclist, &(g->grayagain));
      }
      else if (curr->tt == ((9) | ((0) << 4)) && (((&((((union GCUnion *)((curr))))->upv)))->v != &((&((((union GCUnion *)((curr))))->upv)))->u.value))
        ((curr->marked) &= ((lu_byte)((~(((1<<(5)) | ((1<<(3)) | (1<<(4)))))))));
      else
        ((((curr)->marked) |= ((1<<(5)))));
      p = &curr->next;
    }
  }
}
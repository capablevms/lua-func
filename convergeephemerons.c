
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



extern lu_mem propagateall(global_State *);
extern int traverseephemeron(global_State *, Table *, int);

static void convergeephemerons (global_State *g) {
  int changed;
  int dir = 0;
  do {
    GCObject *w;
    GCObject *next = g->ephemeron;
    g->ephemeron = ((void*)0);
    changed = 0;
    while ((w = next) != ((void*)0)) {
      Table *h = (&((((union GCUnion *)((w))))->h));
      next = h->gclist;
      ((((h)->marked) |= ((1<<(5)))));
      if (traverseephemeron(g, h, dir)) {
        propagateall(g);
        changed = 1;
      }
    }
    dir = !dir;
  } while (changed);
}
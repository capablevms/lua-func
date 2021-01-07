
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
extern GCObject ** getgclist(GCObject *);

static void genlink (global_State *g, GCObject *o) {
  ((void)0);
  if (((o)->marked & 7) == 5) {
    linkgclist_((&(((union GCUnion *)((o)))->gc)), getgclist(o), &(g->grayagain));
  }
  else if (((o)->marked & 7) == 6)
    ((o)->marked ^= ((6)^(4)));
}
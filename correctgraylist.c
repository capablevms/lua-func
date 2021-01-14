
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



extern GCObject ** getgclist(GCObject *);

extern GCObject **correctgraylist (GCObject **p) {
  GCObject *curr;
  while ((curr = *p) != ((void*)0)) {
    GCObject **next = getgclist(curr);
    if ((((curr)->marked) & (((1<<(3)) | (1<<(4))))))
      goto remove;
    else if (((curr)->marked & 7) == 5) {
      ((void)0);
      ((((curr)->marked) |= ((1<<(5)))));
      ((curr)->marked ^= ((5)^(6)));
      goto remain;
    }
    else if (curr->tt == ((8) | ((0) << 4))) {
      ((void)0);
      goto remain;
    }
    else {
      ((void)0);
      if (((curr)->marked & 7) == 6)
        ((curr)->marked ^= ((6)^(4)));
      ((((curr)->marked) |= ((1<<(5)))));
      goto remove;
    }
    remove: *p = *next; continue;
    remain: p = next; continue;
  }
  return p;
}
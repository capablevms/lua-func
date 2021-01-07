
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



extern void freeobj(lua_State *, GCObject *);

static GCObject **sweepgen (lua_State *L, global_State *g, GCObject **p,
                            GCObject *limit, GCObject **pfirstold1) {
  static const lu_byte nextage[] = {
    1,
    3,
    3,
    4,
    4,
    5,
    6
  };
  int white = ((lu_byte)(((g)->currentwhite & ((1<<(3)) | (1<<(4))))));
  GCObject *curr;
  while ((curr = *p) != limit) {
    if ((((curr)->marked) & (((1<<(3)) | (1<<(4)))))) {
      ((void)0);
      *p = curr->next;
      freeobj(L, curr);
    }
    else {
      if (((curr)->marked & 7) == 0) {
        int marked = curr->marked & ~(((1<<(5)) | ((1<<(3)) | (1<<(4)))) | 7);
        curr->marked = ((lu_byte)((marked | 1 | white)));
      }
      else {
        ((curr)->marked = ((lu_byte)((((curr)->marked & (~7)) | nextage[((curr)->marked & 7)]))));
        if (((curr)->marked & 7) == 3 && *pfirstold1 == ((void*)0))
          *pfirstold1 = curr;
      }
      p = &curr->next;
    }
  }
  return p;
}
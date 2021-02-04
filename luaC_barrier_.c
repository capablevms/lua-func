
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



extern void reallymarkobject(global_State *, GCObject *);

void luaC_barrier_ (lua_State *L, GCObject *o, GCObject *v) {
  global_State *g = (L->l_G);
  ((void)0);
  if (((g)->gcstate <= 2)) {
    reallymarkobject(g, v);
    if ((((o)->marked & 7) > 1)) {
      ((void)0);
      ((v)->marked = ((lu_byte)((((v)->marked & (~7)) | 2))));
    }
  }
  else {
    ((void)0);
    if (g->gckind == 0)
      (o->marked = ((lu_byte)(((o->marked & ~((1<<(5)) | ((1<<(3)) | (1<<(4))))) | ((lu_byte)(((g)->currentwhite & ((1<<(3)) | (1<<(4))))))))));
  }
}
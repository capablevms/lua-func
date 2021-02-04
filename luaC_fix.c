
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




void luaC_fix (lua_State *L, GCObject *o) {
  global_State *g = (L->l_G);
  ((void)0);
  ((o->marked) &= ((lu_byte)((~(((1<<(5)) | ((1<<(3)) | (1<<(4)))))))));
  ((o)->marked = ((lu_byte)((((o)->marked & (~7)) | 4))));
  g->allgc = o->next;
  o->next = g->fixedgc;
  g->fixedgc = o;
}
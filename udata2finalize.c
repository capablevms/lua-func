
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




static GCObject *udata2finalize (global_State *g) {
  GCObject *o = g->tobefnz;
  ((void)0);
  g->tobefnz = o->next;
  o->next = g->allgc;
  g->allgc = o;
  ((o->marked) &= ((lu_byte)((~((1<<(6)))))));
  if ((3 <= (g)->gcstate && (g)->gcstate <= 6))
    (o->marked = ((lu_byte)(((o->marked & ~((1<<(5)) | ((1<<(3)) | (1<<(4))))) | ((lu_byte)(((g)->currentwhite & ((1<<(3)) | (1<<(4))))))))));
  else if (((o)->marked & 7) == 3)
    g->firstold1 = o;
  return o;
}
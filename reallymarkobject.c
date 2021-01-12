
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

static void reallymarkobject (global_State *g, GCObject *o) {
  switch (o->tt) {
    case ((4) | ((0) << 4)):
    case ((4) | ((1) << 4)): {
      (o->marked = ((lu_byte)(((o->marked & ~((1<<(3)) | (1<<(4)))) | (1<<(5))))));
      break;
    }
    case ((9) | ((0) << 4)): {
      UpVal *uv = (&((((union GCUnion *)((o))))->upv));
      if (((uv)->v != &(uv)->u.value))
        ((uv->marked) &= ((lu_byte)((~(((1<<(5)) | ((1<<(3)) | (1<<(4)))))))));
      else
        (uv->marked = ((lu_byte)(((uv->marked & ~((1<<(3)) | (1<<(4)))) | (1<<(5))))));
      { ((void)g->mainthread, ((void)0)); if (((((uv->v)->tt_) & (1 << 6)) && ((((((uv->v)->value_).gc))->marked) & (((1<<(3)) | (1<<(4))))))) reallymarkobject(g,(((uv->v)->value_).gc)); };
      break;
    }
    case ((7) | ((0) << 4)): {
      Udata *u = (&((((union GCUnion *)((o))))->u));
      if (u->nuvalue == 0) {
        { if (u->metatable) { if ((((u->metatable)->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g, (&(((union GCUnion *)((u->metatable)))->gc))); }; };
        (u->marked = ((lu_byte)(((u->marked & ~((1<<(3)) | (1<<(4)))) | (1<<(5))))));
        break;
      }

    }
    case ((6) | ((0) << 4)): case ((6) | ((2) << 4)): case ((5) | ((0) << 4)):
    case ((8) | ((0) << 4)): case (((9 +1)) | ((0) << 4)): {
      linkgclist_((&(((union GCUnion *)((o)))->gc)), getgclist(o), &(g->gray));
      break;
    }
    default: ((void)0); break;
  }
}
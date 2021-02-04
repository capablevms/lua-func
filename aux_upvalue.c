
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




extern const char *aux_upvalue (TValue *fi, int n, TValue **val,
                                GCObject **owner) {
  switch (((((fi)->tt_)) & 0x3F)) {
    case ((6) | ((2) << 4)): {
      CClosure *f = ((&((((union GCUnion *)((((fi)->value_).gc))))->cl.c)));
      if (!(((unsigned int)((n))) - 1u < ((unsigned int)((f->nupvalues)))))
        return ((void*)0);
      *val = &f->upvalue[n-1];
      if (owner) *owner = (&(((union GCUnion *)((f)))->gc));
      return "";
    }
    case ((6) | ((0) << 4)): {
      LClosure *f = ((&((((union GCUnion *)((((fi)->value_).gc))))->cl.l)));
      TString *name;
      Proto *p = f->p;
      if (!(((unsigned int)((n))) - 1u < ((unsigned int)((p->sizeupvalues)))))
        return ((void*)0);
      *val = f->upvals[n-1]->v;
      if (owner) *owner = (&(((union GCUnion *)((f->upvals[n - 1])))->gc));
      name = p->upvalues[n-1].name;
      return (name == ((void*)0)) ? "(no name)" : ((name)->contents);
    }
    default: return ((void*)0);
  }
}
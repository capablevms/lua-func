
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



extern void init_var(FuncState *, expdesc *, int);
extern void init_exp(expdesc *, expkind, int);
extern Vardesc * getlocalvardesc(FuncState *, int);

static int searchvar (FuncState *fs, TString *n, expdesc *var) {
  int i;
  for (i = ((int)((fs->nactvar))) - 1; i >= 0; i--) {
    Vardesc *vd = getlocalvardesc(fs, i);
    if (((n) == (vd->vd.name))) {
      if (vd->vd.kind == 3)
        init_exp(var, VCONST, fs->firstlocal + i);
      else
        init_var(fs, var, i);
      return var->k;
    }
  }
  return -1;
}
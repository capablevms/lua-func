
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



extern int registerlocalvar(LexState *, FuncState *, TString *);
extern Vardesc * getlocalvardesc(FuncState *, int);
extern int luaY_nvarstack(FuncState *);

static void adjustlocalvars (LexState *ls, int nvars) {
  FuncState *fs = ls->fs;
  int stklevel = luaY_nvarstack(fs);
  int i;
  for (i = 0; i < nvars; i++) {
    int vidx = fs->nactvar++;
    Vardesc *var = getlocalvardesc(fs, vidx);
    var->vd.sidx = stklevel++;
    var->vd.pidx = registerlocalvar(ls, fs, var->vd.name);
  }
}
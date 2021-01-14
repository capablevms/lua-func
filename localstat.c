
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



extern void checktoclose(LexState *, int);
extern void adjustlocalvars(LexState *, int);
extern void adjust_assign(LexState *, int, int, expdesc *);
extern void adjustlocalvars(LexState *, int);
extern int luaK_exp2const(FuncState *, const expdesc *, TValue *);
extern Vardesc * getlocalvardesc(FuncState *, int);
extern int explist(LexState *, expdesc *);
extern int testnext(LexState *, int);
extern int testnext(LexState *, int);
extern void luaK_semerror(LexState *, const char *);
extern Vardesc * getlocalvardesc(FuncState *, int);
extern int getlocalattribute(LexState *);
extern int new_localvar(LexState *, TString *);
extern TString * str_checkname(LexState *);

extern void localstat (LexState *ls) {

  FuncState *fs = ls->fs;
  int toclose = -1;
  Vardesc *var;
  int vidx, kind;
  int nvars = 0;
  int nexps;
  expdesc e;
  do {
    vidx = new_localvar(ls, str_checkname(ls));
    kind = getlocalattribute(ls);
    getlocalvardesc(fs, vidx)->vd.kind = kind;
    if (kind == 2) {
      if (toclose != -1)
        luaK_semerror(ls, "multiple to-be-closed variables in local list");
      toclose = fs->nactvar + nvars;
    }
    nvars++;
  } while (testnext(ls, ','));
  if (testnext(ls, '='))
    nexps = explist(ls, &e);
  else {
    e.k = VVOID;
    nexps = 0;
  }
  var = getlocalvardesc(fs, vidx);
  if (nvars == nexps &&
      var->vd.kind == 1 &&
      luaK_exp2const(fs, &e, &var->k)) {
    var->vd.kind = 3;
    adjustlocalvars(ls, nvars - 1);
    fs->nactvar++;
  }
  else {
    adjust_assign(ls, nvars, nexps, &e);
    adjustlocalvars(ls, nvars);
  }
  checktoclose(ls, toclose);
}
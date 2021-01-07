
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



extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern int luaY_nvarstack(FuncState *);
extern int solvegotos(LexState *, Labeldesc *);
extern int newlabelentry(LexState *, Labellist *, TString *, int, int);
extern int luaK_getlabel(FuncState *);

static int createlabel (LexState *ls, TString *name, int line,
                        int last) {
  FuncState *fs = ls->fs;
  Labellist *ll = &ls->dyd->label;
  int l = newlabelentry(ls, ll, name, line, luaK_getlabel(fs));
  if (last) {

    ll->arr[l].nactvar = fs->bl->nactvar;
  }
  if (solvegotos(ls, &ll->arr[l])) {
    luaK_codeABCk(fs,OP_CLOSE,luaY_nvarstack(fs),0,0,0);
    return 1;
  }
  return 0;
}
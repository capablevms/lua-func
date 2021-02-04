
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



extern void luaK_patchlist(FuncState *, int, int);
extern int luaK_jump(FuncState *);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern int luaY_nvarstack(FuncState *);
extern int stacklevel(FuncState *, int);
extern int newgotoentry(LexState *, TString *, int, int);
extern int luaK_jump(FuncState *);
extern Labeldesc * findlabel(LexState *, TString *);
extern TString * str_checkname(LexState *);

extern void gotostat (LexState *ls) {
  FuncState *fs = ls->fs;
  int line = ls->linenumber;
  TString *name = str_checkname(ls);
  Labeldesc *lb = findlabel(ls, name);
  if (lb == ((void*)0))

    newgotoentry(ls, name, line, luaK_jump(fs));
  else {

    int lblevel = stacklevel(fs, lb->nactvar);
    if (luaY_nvarstack(fs) > lblevel)
      luaK_codeABCk(fs,OP_CLOSE,lblevel,0,0,0);

    luaK_patchlist(fs, luaK_jump(fs), lb->pc);
  }
}
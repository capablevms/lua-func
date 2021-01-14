
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



extern void luaK_reserveregs(FuncState *, int);
extern void setvararg(FuncState *, int);
extern void adjustlocalvars(LexState *, int);
extern int testnext(LexState *, int);
extern void luaX_syntaxerror(LexState *, const char *);
extern void luaX_next(LexState *);
extern int new_localvar(LexState *, TString *);
extern TString * str_checkname(LexState *);

extern void parlist (LexState *ls) {

  FuncState *fs = ls->fs;
  Proto *f = fs->f;
  int nparams = 0;
  int isvararg = 0;
  if (ls->t.token != ')') {
    do {
      switch (ls->t.token) {
        case TK_NAME: {
          new_localvar(ls, str_checkname(ls));
          nparams++;
          break;
        }
        case TK_DOTS: {
          luaX_next(ls);
          isvararg = 1;
          break;
        }
        default: luaX_syntaxerror(ls, "<name> or '...' expected");
      }
    } while (!isvararg && testnext(ls, ','));
  }
  adjustlocalvars(ls, nparams);
  f->numparams = ((lu_byte)((fs->nactvar)));
  if (isvararg)
    setvararg(fs, f->numparams);
  luaK_reserveregs(fs, fs->nactvar);
}
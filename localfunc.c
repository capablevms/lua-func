
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

typedef struct BlockCnt {
  struct BlockCnt *previous;
  int firstlabel;
  int firstgoto;
  lu_byte nactvar;
  lu_byte upval;
  lu_byte isloop;
  lu_byte insidetbc;
} BlockCnt;


extern LocVar * localdebuginfo(FuncState *, int);
extern void body(LexState *, expdesc *, int, int);
extern void adjustlocalvars(LexState *, int);
extern int new_localvar(LexState *, TString *);
extern TString * str_checkname(LexState *);

static void localfunc (LexState *ls) {
  expdesc b;
  FuncState *fs = ls->fs;
  int fvar = fs->nactvar;
  new_localvar(ls, str_checkname(ls));
  adjustlocalvars(ls, 1);
  body(ls, &b, 0, ls->linenumber);

  localdebuginfo(fs, fvar)->startpc = fs->pc;
}

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

typedef struct ConsControl {
  expdesc v;
  expdesc *t;
  int nh;
  int na;
  int tostore;
} ConsControl;


extern void luaK_fixline(FuncState *, int);
extern void init_exp(expdesc *, expkind, int);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern void luaK_exp2nextreg(FuncState *, expdesc *);
extern void luaX_syntaxerror(LexState *, const char *);
extern void luaX_next(LexState *);
extern void codestring(expdesc *, TString *);
extern void constructor(LexState *, expdesc *);
extern void check_match(LexState *, int, int, int);
extern void luaK_setreturns(FuncState *, expdesc *, int);
extern int explist(LexState *, expdesc *);
extern void luaX_next(LexState *);

static void funcargs (LexState *ls, expdesc *f, int line) {
  FuncState *fs = ls->fs;
  expdesc args;
  int base, nparams;
  switch (ls->t.token) {
    case '(': {
      luaX_next(ls);
      if (ls->t.token == ')')
        args.k = VVOID;
      else {
        explist(ls, &args);
        if (((args.k) == VCALL || (args.k) == VVARARG))
          luaK_setreturns(fs, &args, (-1));
      }
      check_match(ls, ')', '(', line);
      break;
    }
    case '{': {
      constructor(ls, &args);
      break;
    }
    case TK_STRING: {
      codestring(&args, ls->t.seminfo.ts);
      luaX_next(ls);
      break;
    }
    default: {
      luaX_syntaxerror(ls, "function arguments expected");
    }
  }
  ((void)0);
  base = f->u.info;
  if (((args.k) == VCALL || (args.k) == VVARARG))
    nparams = (-1);
  else {
    if (args.k != VVOID)
      luaK_exp2nextreg(fs, &args);
    nparams = fs->freereg - (base+1);
  }
  init_exp(f, VCALL, luaK_codeABCk(fs,OP_CALL,base,nparams+1,2,0));
  luaK_fixline(fs, line);
  fs->freereg = base+1;

}
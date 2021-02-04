
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

extern int testnext(LexState *, int);
extern void luaK_ret(FuncState *, int, int);
extern void luaK_exp2nextreg(FuncState *, expdesc *);
extern int luaK_exp2anyreg(FuncState *, expdesc *);
extern void luaK_setreturns(FuncState *, expdesc *, int);
extern int explist(LexState *, expdesc *);
extern int block_follow(LexState *, int);
extern int luaY_nvarstack(FuncState *);

extern void retstat (LexState *ls) {

  FuncState *fs = ls->fs;
  expdesc e;
  int nret;
  int first = luaY_nvarstack(fs);
  if (block_follow(ls, 1) || ls->t.token == ';')
    nret = 0;
  else {
    nret = explist(ls, &e);
    if (((e.k) == VCALL || (e.k) == VVARARG)) {
      luaK_setreturns(fs, &e, (-1));
      if (e.k == VCALL && nret == 1 && !fs->bl->insidetbc) {
        ((((fs)->f->code[(&e)->u.info])) = (((((fs)->f->code[(&e)->u.info]))&(~((~((~(Instruction)0)<<(7)))<<(0)))) | ((((Instruction)(OP_TAILCALL))<<0)&((~((~(Instruction)0)<<(7)))<<(0)))));
        ((void)0);
      }
      nret = (-1);
    }
    else {
      if (nret == 1)
        first = luaK_exp2anyreg(fs, &e);
      else {
        luaK_exp2nextreg(fs, &e);
        ((void)0);
      }
    }
  }
  luaK_ret(fs, first, nret);
  testnext(ls, ';');
}
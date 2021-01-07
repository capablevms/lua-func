
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



extern void luaX_syntaxerror(LexState *, const char *);
extern void restassign(LexState *, struct LHS_assign *, int);
extern void suffixedexp(LexState *, expdesc *);

static void exprstat (LexState *ls) {

  FuncState *fs = ls->fs;
  struct LHS_assign v;
  suffixedexp(ls, &v.v);
  if (ls->t.token == '=' || ls->t.token == ',') {
    v.prev = ((void*)0);
    restassign(ls, &v, 1);
  }
  else {
    Instruction *inst;
    { if (!(v.v.k == VCALL)) luaX_syntaxerror(ls, "syntax error"); };
    inst = &((fs)->f->code[(&v.v)->u.info]);
    ((*inst) = (((*inst)&(~((~((~(Instruction)0)<<(8)))<<(((((0 + 7) + 8) + 1) + 8))))) | ((((Instruction)(1))<<((((0 + 7) + 8) + 1) + 8))&((~((~(Instruction)0)<<(8)))<<(((((0 + 7) + 8) + 1) + 8))))));
  }
}
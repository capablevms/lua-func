
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
typedef struct ConsControl {
  expdesc v;
  expdesc *t;
  int nh;
  int na;
  int tostore;
} ConsControl;


extern void luaX_next(LexState *);
extern void suffixedexp(LexState *, expdesc *);
extern void body(LexState *, expdesc *, int, int);
extern void luaX_next(LexState *);
extern void constructor(LexState *, expdesc *);
extern void init_exp(expdesc *, expkind, int);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern void luaX_syntaxerror(LexState *, const char *);
extern void init_exp(expdesc *, expkind, int);
extern void init_exp(expdesc *, expkind, int);
extern void init_exp(expdesc *, expkind, int);
extern void codestring(expdesc *, TString *);
extern void init_exp(expdesc *, expkind, int);
extern void init_exp(expdesc *, expkind, int);

extern void simpleexp (LexState *ls, expdesc *v) {


  switch (ls->t.token) {
    case TK_FLT: {
      init_exp(v, VKFLT, 0);
      v->u.nval = ls->t.seminfo.r;
      break;
    }
    case TK_INT: {
      init_exp(v, VKINT, 0);
      v->u.ival = ls->t.seminfo.i;
      break;
    }
    case TK_STRING: {
      codestring(v, ls->t.seminfo.ts);
      break;
    }
    case TK_NIL: {
      init_exp(v, VNIL, 0);
      break;
    }
    case TK_TRUE: {
      init_exp(v, VTRUE, 0);
      break;
    }
    case TK_FALSE: {
      init_exp(v, VFALSE, 0);
      break;
    }
    case TK_DOTS: {
      FuncState *fs = ls->fs;
      { if (!(fs->f->is_vararg)) luaX_syntaxerror(ls, "cannot use '...' outside a vararg function"); };

      init_exp(v, VVARARG, luaK_codeABCk(fs,OP_VARARG,0,0,1,0));
      break;
    }
    case '{': {
      constructor(ls, v);
      return;
    }
    case TK_FUNCTION: {
      luaX_next(ls);
      body(ls, v, 0, ls->linenumber);
      return;
    }
    default: {
      suffixedexp(ls, v);
      return;
    }
  }
  luaX_next(ls);
}
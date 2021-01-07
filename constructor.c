
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


extern void luaK_settablesize(FuncState *, int, int, int, int);
extern void lastlistfield(FuncState *, ConsControl *);
extern void check_match(LexState *, int, int, int);
extern int testnext(LexState *, int);
extern int testnext(LexState *, int);
extern void field(LexState *, ConsControl *);
extern void closelistfield(FuncState *, ConsControl *);
extern void checknext(LexState *, int);
extern void init_exp(expdesc *, expkind, int);
extern void luaK_reserveregs(FuncState *, int);
extern void init_exp(expdesc *, expkind, int);
extern int luaK_code(FuncState *, Instruction);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);

static void constructor (LexState *ls, expdesc *t) {


  FuncState *fs = ls->fs;
  int line = ls->linenumber;
  int pc = luaK_codeABCk(fs,OP_NEWTABLE,0,0,0,0);
  ConsControl cc;
  luaK_code(fs, 0);
  cc.na = cc.nh = cc.tostore = 0;
  cc.t = t;
  init_exp(t, VNONRELOC, fs->freereg);
  luaK_reserveregs(fs, 1);
  init_exp(&cc.v, VVOID, 0);
  checknext(ls, '{');
  do {
    ((void)0);
    if (ls->t.token == '}') break;
    closelistfield(fs, &cc);
    field(ls, &cc);
  } while (testnext(ls, ',') || testnext(ls, ';'));
  check_match(ls, '}', '{', line);
  lastlistfield(fs, &cc);
  luaK_settablesize(fs, pc, t->u.info, cc.na, cc.nh);
}
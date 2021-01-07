
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


extern void luaK_fixline(FuncState *, int);
extern void fixforjump(FuncState *, int, int, int);
extern int luaK_codeABx(FuncState *, OpCode, int, unsigned int);
extern void luaK_fixline(FuncState *, int);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern void fixforjump(FuncState *, int, int, int);
extern int luaK_getlabel(FuncState *);
extern void leaveblock(FuncState *);
extern void block(LexState *);
extern void luaK_reserveregs(FuncState *, int);
extern void adjustlocalvars(LexState *, int);
extern void enterblock(FuncState *, BlockCnt *, lu_byte);
extern int luaK_codeABx(FuncState *, OpCode, int, unsigned int);
extern void checknext(LexState *, int);

static void forbody (LexState *ls, int base, int line, int nvars, int isgen) {

  static const OpCode forprep[2] = {OP_FORPREP, OP_TFORPREP};
  static const OpCode forloop[2] = {OP_FORLOOP, OP_TFORLOOP};
  BlockCnt bl;
  FuncState *fs = ls->fs;
  int prep, endfor;
  checknext(ls, TK_DO);
  prep = luaK_codeABx(fs, forprep[isgen], base, 0);
  enterblock(fs, &bl, 0);
  adjustlocalvars(ls, nvars);
  luaK_reserveregs(fs, nvars);
  block(ls);
  leaveblock(fs);
  fixforjump(fs, prep, luaK_getlabel(fs), 0);
  if (isgen) {
    luaK_codeABCk(fs,OP_TFORCALL,base,0,nvars,0);
    luaK_fixline(fs, line);
  }
  endfor = luaK_codeABx(fs, forloop[isgen], base, 0);
  fixforjump(fs, endfor, prep + 1, 1);
  luaK_fixline(fs, line);
}
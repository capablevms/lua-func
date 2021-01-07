
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


extern void leaveblock(FuncState *);
extern void luaK_patchlist(FuncState *, int, int);
extern void luaK_patchtohere(FuncState *, int);
extern int luaK_jump(FuncState *);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern int stacklevel(FuncState *, int);
extern void luaK_patchtohere(FuncState *, int);
extern int luaK_jump(FuncState *);
extern void leaveblock(FuncState *);
extern int cond(LexState *);
extern void check_match(LexState *, int, int, int);
extern void statlist(LexState *);
extern void luaX_next(LexState *);
extern void enterblock(FuncState *, BlockCnt *, lu_byte);
extern void enterblock(FuncState *, BlockCnt *, lu_byte);
extern int luaK_getlabel(FuncState *);

static void repeatstat (LexState *ls, int line) {

  int condexit;
  FuncState *fs = ls->fs;
  int repeat_init = luaK_getlabel(fs);
  BlockCnt bl1, bl2;
  enterblock(fs, &bl1, 1);
  enterblock(fs, &bl2, 0);
  luaX_next(ls);
  statlist(ls);
  check_match(ls, TK_UNTIL, TK_REPEAT, line);
  condexit = cond(ls);
  leaveblock(fs);
  if (bl2.upval) {
    int exit = luaK_jump(fs);
    luaK_patchtohere(fs, condexit);
    luaK_codeABCk(fs,OP_CLOSE,stacklevel(fs, bl2.nactvar),0,0,0);
    condexit = luaK_jump(fs);
    luaK_patchtohere(fs, exit);
  }
  luaK_patchlist(fs, condexit, repeat_init);
  leaveblock(fs);
}
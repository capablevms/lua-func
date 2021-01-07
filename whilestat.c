
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


extern void luaK_patchtohere(FuncState *, int);
extern void leaveblock(FuncState *);
extern void check_match(LexState *, int, int, int);
extern void luaK_patchlist(FuncState *, int, int);
extern int luaK_jump(FuncState *);
extern void block(LexState *);
extern void checknext(LexState *, int);
extern void enterblock(FuncState *, BlockCnt *, lu_byte);
extern int cond(LexState *);
extern int luaK_getlabel(FuncState *);
extern void luaX_next(LexState *);

static void whilestat (LexState *ls, int line) {

  FuncState *fs = ls->fs;
  int whileinit;
  int condexit;
  BlockCnt bl;
  luaX_next(ls);
  whileinit = luaK_getlabel(fs);
  condexit = cond(ls);
  enterblock(fs, &bl, 1);
  checknext(ls, TK_DO);
  block(ls);
  luaK_patchlist(fs, luaK_jump(fs), whileinit);
  check_match(ls, TK_END, TK_WHILE, line);
  leaveblock(fs);
  luaK_patchtohere(fs, condexit);
}
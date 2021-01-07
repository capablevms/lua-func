
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
extern void luaK_concat(FuncState *, int *, int);
extern int luaK_jump(FuncState *);
extern void leaveblock(FuncState *);
extern void statlist(LexState *);
extern void enterblock(FuncState *, BlockCnt *, lu_byte);
extern void luaK_goiftrue(FuncState *, expdesc *);
extern int luaK_jump(FuncState *);
extern void leaveblock(FuncState *);
extern int block_follow(LexState *, int);
extern int testnext(LexState *, int);
extern void luaK_patchlist(FuncState *, int, int);
extern int newgotoentry(LexState *, TString *, int, int);
extern void enterblock(FuncState *, BlockCnt *, lu_byte);
extern void luaK_goiffalse(FuncState *, expdesc *);
extern int issinglejump(LexState *, TString **, int *);
extern void checknext(LexState *, int);
extern void expr(LexState *, expdesc *);
extern void luaX_next(LexState *);

static void test_then_block (LexState *ls, int *escapelist) {

  BlockCnt bl;
  int line;
  FuncState *fs = ls->fs;
  TString *jlb = ((void*)0);
  int target = (-1);
  expdesc v;
  int jf;
  luaX_next(ls);
  expr(ls, &v);
  checknext(ls, TK_THEN);
  line = ls->linenumber;
  if (issinglejump(ls, &jlb, &target)) {
    luaK_goiffalse(ls->fs, &v);
    enterblock(fs, &bl, 0);
    if (jlb != ((void*)0))
      newgotoentry(ls, jlb, line, v.t);
    else
      luaK_patchlist(fs, v.t, target);
    while (testnext(ls, ';')) {}
    if (block_follow(ls, 0)) {
      leaveblock(fs);
      return;
    }
    else
      jf = luaK_jump(fs);
  }
  else {
    luaK_goiftrue(ls->fs, &v);
    enterblock(fs, &bl, 0);
    jf = v.f;
  }
  statlist(ls);
  leaveblock(fs);
  if (ls->t.token == TK_ELSE ||
      ls->t.token == TK_ELSEIF)
    luaK_concat(fs, escapelist, luaK_jump(fs));
  luaK_patchtohere(fs, jf);
}
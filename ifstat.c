
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
extern void check_match(LexState *, int, int, int);
extern void block(LexState *);
extern int testnext(LexState *, int);
extern void test_then_block(LexState *, int *);
extern void test_then_block(LexState *, int *);

extern void ifstat (LexState *ls, int line) {

  FuncState *fs = ls->fs;
  int escapelist = (-1);
  test_then_block(ls, &escapelist);
  while (ls->t.token == TK_ELSEIF)
    test_then_block(ls, &escapelist);
  if (testnext(ls, TK_ELSE))
    block(ls);
  check_match(ls, TK_END, TK_IF, line);
  luaK_patchtohere(fs, escapelist);
}
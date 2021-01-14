
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
extern void check_match(LexState *, int, int, int);
extern void luaX_syntaxerror(LexState *, const char *);
extern void forlist(LexState *, TString *);
extern void fornum(LexState *, TString *, int);
extern TString * str_checkname(LexState *);
extern void luaX_next(LexState *);
extern void enterblock(FuncState *, BlockCnt *, lu_byte);

extern void forstat (LexState *ls, int line) {

  FuncState *fs = ls->fs;
  TString *varname;
  BlockCnt bl;
  enterblock(fs, &bl, 1);
  luaX_next(ls);
  varname = str_checkname(ls);
  switch (ls->t.token) {
    case '=': fornum(ls, varname, line); break;
    case ',': case TK_IN: forlist(ls, varname); break;
    default: luaX_syntaxerror(ls, "'=' or 'in' expected");
  }
  check_match(ls, TK_END, TK_FOR, line);
  leaveblock(fs);
}
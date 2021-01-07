
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


extern void forbody(LexState *, int, int, int, int);
extern void luaK_checkstack(FuncState *, int);
extern void markupval(FuncState *, int);
extern void adjustlocalvars(LexState *, int);
extern void adjust_assign(LexState *, int, int, expdesc *);
extern int explist(LexState *, expdesc *);
extern void checknext(LexState *, int);
extern int new_localvar(LexState *, TString *);
extern TString * str_checkname(LexState *);
extern int testnext(LexState *, int);
extern int new_localvar(LexState *, TString *);
extern int new_localvar(LexState *, TString *);
extern TString * luaX_newstring(LexState *, const char *, size_t);
extern int new_localvar(LexState *, TString *);
extern TString * luaX_newstring(LexState *, const char *, size_t);
extern int new_localvar(LexState *, TString *);
extern TString * luaX_newstring(LexState *, const char *, size_t);
extern int new_localvar(LexState *, TString *);
extern TString * luaX_newstring(LexState *, const char *, size_t);

static void forlist (LexState *ls, TString *indexname) {

  FuncState *fs = ls->fs;
  expdesc e;
  int nvars = 5;
  int line;
  int base = fs->freereg;

  new_localvar(ls, luaX_newstring(ls, "" "(for state)", (sizeof("(for state)")/sizeof(char)) - 1));;
  new_localvar(ls, luaX_newstring(ls, "" "(for state)", (sizeof("(for state)")/sizeof(char)) - 1));;
  new_localvar(ls, luaX_newstring(ls, "" "(for state)", (sizeof("(for state)")/sizeof(char)) - 1));;
  new_localvar(ls, luaX_newstring(ls, "" "(for state)", (sizeof("(for state)")/sizeof(char)) - 1));;

  new_localvar(ls, indexname);
  while (testnext(ls, ',')) {
    new_localvar(ls, str_checkname(ls));
    nvars++;
  }
  checknext(ls, TK_IN);
  line = ls->linenumber;
  adjust_assign(ls, 4, explist(ls, &e), &e);
  adjustlocalvars(ls, 4);
  markupval(fs, fs->nactvar);
  luaK_checkstack(fs, 3);
  forbody(ls, base, line, nvars - 4, 1);
}
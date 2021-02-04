
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


extern void close_func(LexState *);
extern void codeclosure(LexState *, expdesc *);
extern void check_match(LexState *, int, int, int);
extern void statlist(LexState *);
extern void checknext(LexState *, int);
extern void parlist(LexState *);
extern void adjustlocalvars(LexState *, int);
extern int new_localvar(LexState *, TString *);
extern TString * luaX_newstring(LexState *, const char *, size_t);
extern void checknext(LexState *, int);
extern void open_func(LexState *, FuncState *, BlockCnt *);
extern Proto * addprototype(LexState *);

extern void body (LexState *ls, expdesc *e, int ismethod, int line) {

  FuncState new_fs;
  BlockCnt bl;
  new_fs.f = addprototype(ls);
  new_fs.f->linedefined = line;
  open_func(ls, &new_fs, &bl);
  checknext(ls, '(');
  if (ismethod) {
    new_localvar(ls, luaX_newstring(ls, "" "self", (sizeof("self")/sizeof(char)) - 1));;
    adjustlocalvars(ls, 1);
  }
  parlist(ls);
  checknext(ls, ')');
  statlist(ls);
  new_fs.f->lastlinedefined = ls->linenumber;
  check_match(ls, TK_END, TK_FUNCTION, line);
  codeclosure(ls, e);
  close_func(ls);
}
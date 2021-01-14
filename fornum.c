
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
extern void adjustlocalvars(LexState *, int);
extern void luaK_reserveregs(FuncState *, int);
extern void luaK_int(FuncState *, int, lua_Integer);
extern void exp1(LexState *);
extern int testnext(LexState *, int);
extern void exp1(LexState *);
extern void checknext(LexState *, int);
extern void exp1(LexState *);
extern void checknext(LexState *, int);
extern int new_localvar(LexState *, TString *);
extern int new_localvar(LexState *, TString *);
extern TString * luaX_newstring(LexState *, const char *, size_t);
extern int new_localvar(LexState *, TString *);
extern TString * luaX_newstring(LexState *, const char *, size_t);
extern int new_localvar(LexState *, TString *);
extern TString * luaX_newstring(LexState *, const char *, size_t);

extern void fornum (LexState *ls, TString *varname, int line) {

  FuncState *fs = ls->fs;
  int base = fs->freereg;
  new_localvar(ls, luaX_newstring(ls, "" "(for state)", (sizeof("(for state)")/sizeof(char)) - 1));;
  new_localvar(ls, luaX_newstring(ls, "" "(for state)", (sizeof("(for state)")/sizeof(char)) - 1));;
  new_localvar(ls, luaX_newstring(ls, "" "(for state)", (sizeof("(for state)")/sizeof(char)) - 1));;
  new_localvar(ls, varname);
  checknext(ls, '=');
  exp1(ls);
  checknext(ls, ',');
  exp1(ls);
  if (testnext(ls, ','))
    exp1(ls);
  else {
    luaK_int(fs, fs->freereg, 1);
    luaK_reserveregs(fs, 1);
  }
  adjustlocalvars(ls, 3);
  forbody(ls, base, line, 1, 0);
}
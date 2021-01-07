
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



extern int createlabel(LexState *, TString *, int, int);
extern int block_follow(LexState *, int);
extern void checkrepeated(LexState *, TString *);
extern void statement(LexState *);
extern void checknext(LexState *, int);

static void labelstat (LexState *ls, TString *name, int line) {

  checknext(ls, TK_DBCOLON);
  while (ls->t.token == ';' || ls->t.token == TK_DBCOLON)
    statement(ls);
  checkrepeated(ls, name);
  createlabel(ls, name, line, block_follow(ls, 0));
}

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


extern int luaY_nvarstack(FuncState *);
extern void exprstat(LexState *);
extern void gotostat(LexState *);
extern void luaX_next(LexState *);
extern void breakstat(LexState *);
extern void retstat(LexState *);
extern void luaX_next(LexState *);
extern void labelstat(LexState *, TString *, int);
extern TString * str_checkname(LexState *);
extern void luaX_next(LexState *);
extern void localstat(LexState *);
extern void localfunc(LexState *);
extern int testnext(LexState *, int);
extern void luaX_next(LexState *);
extern void funcstat(LexState *, int);
extern void repeatstat(LexState *, int);
extern void forstat(LexState *, int);
extern void check_match(LexState *, int, int, int);
extern void block(LexState *);
extern void luaX_next(LexState *);
extern void whilestat(LexState *, int);
extern void ifstat(LexState *, int);
extern void luaX_next(LexState *);
extern void luaE_incCstack(lua_State *);

static void statement (LexState *ls) {
  int line = ls->linenumber;
  luaE_incCstack(ls->L);
  switch (ls->t.token) {
    case ';': {
      luaX_next(ls);
      break;
    }
    case TK_IF: {
      ifstat(ls, line);
      break;
    }
    case TK_WHILE: {
      whilestat(ls, line);
      break;
    }
    case TK_DO: {
      luaX_next(ls);
      block(ls);
      check_match(ls, TK_END, TK_DO, line);
      break;
    }
    case TK_FOR: {
      forstat(ls, line);
      break;
    }
    case TK_REPEAT: {
      repeatstat(ls, line);
      break;
    }
    case TK_FUNCTION: {
      funcstat(ls, line);
      break;
    }
    case TK_LOCAL: {
      luaX_next(ls);
      if (testnext(ls, TK_FUNCTION))
        localfunc(ls);
      else
        localstat(ls);
      break;
    }
    case TK_DBCOLON: {
      luaX_next(ls);
      labelstat(ls, str_checkname(ls), line);
      break;
    }
    case TK_RETURN: {
      luaX_next(ls);
      retstat(ls);
      break;
    }
    case TK_BREAK: {
      breakstat(ls);
      break;
    }
    case TK_GOTO: {
      luaX_next(ls);
      gotostat(ls);
      break;
    }
    default: {
      exprstat(ls);
      break;
    }
  }
  ((void)0);

  ls->fs->freereg = luaY_nvarstack(ls->fs);
  ((ls)->L->nCcalls--);
}
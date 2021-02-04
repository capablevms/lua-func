
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



extern void luaX_next(LexState *);
extern void luaX_next(LexState *);
extern int stacklevel(FuncState *, int);
extern int luaY_nvarstack(FuncState *);
extern Labeldesc * findlabel(LexState *, TString *);
extern int luaX_lookahead(LexState *);
extern TString * luaS_newlstr(lua_State *, const char *, size_t);
extern int testnext(LexState *, int);

extern int issinglejump (LexState *ls, TString **label, int *target) {
  if (testnext(ls, TK_BREAK)) {
    *label = (luaS_newlstr(ls->L, "" "break", (sizeof("break")/sizeof(char))-1));
    return 1;
  }
  else if (ls->t.token != TK_GOTO || luaX_lookahead(ls) != TK_NAME)
    return 0;
  else {
    TString *lname = ls->lookahead.seminfo.ts;
    Labeldesc *lb = findlabel(ls, lname);
    if (lb) {

      if (luaY_nvarstack(ls->fs) > stacklevel(ls->fs, lb->nactvar))
        return 0;
      *target = lb->pc;
    }
    else
      *label = lname;
    luaX_next(ls);
    luaX_next(ls);
    return 1;
  }
}
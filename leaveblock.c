
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


extern void undefgoto(LexState *, Labeldesc *);
extern void movegotosout(FuncState *, BlockCnt *);
extern void removevars(FuncState *, int);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern int createlabel(LexState *, TString *, int, int);
extern TString * luaS_newlstr(lua_State *, const char *, size_t);
extern int stacklevel(FuncState *, int);

static void leaveblock (FuncState *fs) {
  BlockCnt *bl = fs->bl;
  LexState *ls = fs->ls;
  int hasclose = 0;
  int stklevel = stacklevel(fs, bl->nactvar);
  if (bl->isloop)
    hasclose = createlabel(ls, (luaS_newlstr(ls->L, "" "break", (sizeof("break")/sizeof(char))-1)), 0, 0);
  if (!hasclose && bl->previous && bl->upval)
    luaK_codeABCk(fs,OP_CLOSE,stklevel,0,0,0);
  fs->bl = bl->previous;
  removevars(fs, bl->nactvar);
  ((void)0);
  fs->freereg = stklevel;
  ls->dyd->label.n = bl->firstlabel;
  if (bl->previous)
    movegotosout(fs, bl);
  else {
    if (bl->firstgoto < ls->dyd->gt.n)
      undefgoto(ls, &ls->dyd->gt.arr[bl->firstgoto]);
  }
}
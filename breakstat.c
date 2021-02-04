
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



extern int newgotoentry(LexState *, TString *, int, int);
extern int luaK_jump(FuncState *);
extern TString * luaS_newlstr(lua_State *, const char *, size_t);
extern void luaX_next(LexState *);

extern void breakstat (LexState *ls) {
  int line = ls->linenumber;
  luaX_next(ls);
  newgotoentry(ls, (luaS_newlstr(ls->L, "" "break", (sizeof("break")/sizeof(char))-1)), line, luaK_jump(ls->fs));
}
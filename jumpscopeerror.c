
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



extern void luaK_semerror(LexState *, const char *);
extern const char * luaO_pushfstring(lua_State *, const char *, ...);
extern Vardesc * getlocalvardesc(FuncState *, int);

static void __attribute__((noreturn)) jumpscopeerror (LexState *ls, Labeldesc *gt) {
  const char *varname = ((getlocalvardesc(ls->fs, gt->nactvar)->vd.name)->contents);
  const char *msg = "<goto %s> at line %d jumps into the scope of local '%s'";
  msg = luaO_pushfstring(ls->L, msg, ((gt->name)->contents), gt->line, varname);
  luaK_semerror(ls, msg);
}
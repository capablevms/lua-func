
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



extern void luaG_concaterror(lua_State *, const TValue *, const TValue *);
extern int callbinTM(lua_State *, const TValue *, const TValue *, StkId, TMS);

extern void luaT_tryconcatTM (lua_State *L) {
  StkId top = L->top;
  if (!callbinTM(L, (&(top - 2)->val), (&(top - 1)->val), top - 2, TM_CONCAT))
    luaG_concaterror(L, (&(top - 2)->val), (&(top - 1)->val));
}
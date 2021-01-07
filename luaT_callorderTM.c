
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



extern void luaG_ordererror(lua_State *, const TValue *, const TValue *);
extern int callbinTM(lua_State *, const TValue *, const TValue *, StkId, TMS);

int luaT_callorderTM (lua_State *L, const TValue *p1, const TValue *p2,
                      TMS event) {
  if (callbinTM(L, p1, p2, L->top, event))
    return !((((((&(L->top)->val)))->tt_) == (((1) | ((0) << 4)))) || ((((((((&(L->top)->val)))->tt_)) & 0x0F)) == (0)));
# 215 "ltm.c"
  luaG_ordererror(L, p1, p2);
  return 0;
}
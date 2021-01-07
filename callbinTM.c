
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



extern void luaT_callTMres(lua_State *, const TValue *, const TValue *, const TValue *, StkId);
extern const TValue * luaT_gettmbyobj(lua_State *, const TValue *, TMS);
extern const TValue * luaT_gettmbyobj(lua_State *, const TValue *, TMS);

static int callbinTM (lua_State *L, const TValue *p1, const TValue *p2,
                      StkId res, TMS event) {
  const TValue *tm = luaT_gettmbyobj(L, p1, event);
  if ((((((((tm))->tt_)) & 0x0F)) == (0)))
    tm = luaT_gettmbyobj(L, p2, event);
  if ((((((((tm))->tt_)) & 0x0F)) == (0))) return 0;
  luaT_callTMres(L, tm, p1, p2, res);
  return 1;
}
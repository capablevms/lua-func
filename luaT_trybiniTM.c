
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



extern void luaT_trybinassocTM(lua_State *, const TValue *, const TValue *, int, StkId, TMS);

void luaT_trybiniTM (lua_State *L, const TValue *p1, lua_Integer i2,
                                   int flip, StkId res, TMS event) {
  TValue aux;
  { TValue *io=(&aux); ((io)->value_).i=(i2); ((io)->tt_=(((3) | ((0) << 4)))); };
  luaT_trybinassocTM(L, p1, &aux, flip, res, event);
}
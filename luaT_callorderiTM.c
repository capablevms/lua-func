
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



extern int luaT_callorderTM(lua_State *, const TValue *, const TValue *, TMS);

int luaT_callorderiTM (lua_State *L, const TValue *p1, int v2,
                       int flip, int isfloat, TMS event) {
  TValue aux; const TValue *p2;
  if (isfloat) {
    { TValue *io=(&aux); ((io)->value_).n=(((lua_Number)((v2)))); ((io)->tt_=(((3) | ((1) << 4)))); };
  }
  else
    { TValue *io=(&aux); ((io)->value_).i=(v2); ((io)->tt_=(((3) | ((0) << 4)))); };
  if (flip) {
    p2 = p1; p1 = &aux;
  }
  else
    p2 = &aux;
  return luaT_callorderTM(L, p1, p2, event);
}
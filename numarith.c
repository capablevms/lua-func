
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



extern lua_Number luaV_modf(lua_State *, lua_Number, lua_Number);
extern double floor(double);
extern double pow(double, double);

static lua_Number numarith (lua_State *L, int op, lua_Number v1,
                                                  lua_Number v2) {
  switch (op) {
    case 0: return ((v1)+(v2));
    case 1: return ((v1)-(v2));
    case 2: return ((v1)*(v2));
    case 5: return ((v1)/(v2));
    case 4: return ((void)L, pow(v1,v2));
    case 6: return ((void)L, (floor(((v1)/(v2)))));
    case 12: return (-(v1));
    case 3: return luaV_modf(L, v1, v2);
    default: ((void)0); return 0;
  }
}
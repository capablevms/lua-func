
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



extern void luaG_opinterror(lua_State *, const TValue *, const TValue *, const char *);
extern void luaG_opinterror(lua_State *, const TValue *, const TValue *, const char *);
extern void luaG_tointerror(lua_State *, const TValue *, const TValue *);
extern int callbinTM(lua_State *, const TValue *, const TValue *, StkId, TMS);

void luaT_trybinTM (lua_State *L, const TValue *p1, const TValue *p2,
                    StkId res, TMS event) {
  if (!callbinTM(L, p1, p2, res, event)) {
    switch (event) {
      case TM_BAND: case TM_BOR: case TM_BXOR:
      case TM_SHL: case TM_SHR: case TM_BNOT: {
        if ((((((((p1))->tt_)) & 0x0F)) == (3)) && (((((((p2))->tt_)) & 0x0F)) == (3)))
          luaG_tointerror(L, p1, p2);
        else
          luaG_opinterror(L, p1, p2, "perform bitwise operation on");
      }

      default:
        luaG_opinterror(L, p1, p2, "perform arithmetic on");
    }
  }
}
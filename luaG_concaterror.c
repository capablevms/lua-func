
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



extern void luaG_typeerror(lua_State *, const TValue *, const char *);

void __attribute__((noreturn)) luaG_concaterror (lua_State *L, const TValue *p1, const TValue *p2) {
  if ((((((((p1))->tt_)) & 0x0F)) == (4)) || (((((((p1))->tt_)) & 0x0F)) == (3))) p1 = p2;
  luaG_typeerror(L, p1, "concatenate");
}
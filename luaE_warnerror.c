
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



extern void luaE_warning(lua_State *, const char *, int);
extern void luaE_warning(lua_State *, const char *, int);
extern void luaE_warning(lua_State *, const char *, int);
extern void luaE_warning(lua_State *, const char *, int);
extern void luaE_warning(lua_State *, const char *, int);

void luaE_warnerror (lua_State *L, const char *where) {
  TValue *errobj = (&(L->top - 1)->val);
  const char *msg = ((((((((errobj))->tt_)) & 0x0F)) == (4)))
                  ? ((((&((((union GCUnion *)((((errobj)->value_).gc))))->ts))))->contents)
                  : "error object is not a string";

  luaE_warning(L, "error in ", 1);
  luaE_warning(L, where, 1);
  luaE_warning(L, " (", 1);
  luaE_warning(L, msg, 1);
  luaE_warning(L, ")", 0);
}

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



extern int auxgetstr(lua_State *, const TValue *, const char *);
extern const TValue * luaH_getint(Table *, lua_Integer);

extern int lua_getglobal (lua_State *L, const char *name) {
  Table *reg;
  ((void) 0);
  reg = ((&((((union GCUnion *)((((&(L->l_G)->l_registry)->value_).gc))))->h)));
  return auxgetstr(L, luaH_getint(reg, 2), name);
}
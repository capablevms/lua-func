
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



extern void luaG_errormsg(lua_State *);
extern void luaD_throw(lua_State *, int);

extern int lua_error (lua_State *L) {
  TValue *errobj;
  ((void) 0);
  errobj = (&(L->top - 1)->val);
  ((void)L, ((void)0));

  if (((((errobj))->tt_) == (((((4) | ((0) << 4))) | (1 << 6)))) && ((((&((((union GCUnion *)((((errobj)->value_).gc))))->ts)))) == ((L->l_G)->memerrmsg)))
    luaD_throw(L, 4);
  else
    luaG_errormsg(L);

  return 0;
}
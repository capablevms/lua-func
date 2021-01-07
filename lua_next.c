
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



extern int luaH_next(lua_State *, Table *, StkId);
extern Table * gettable(lua_State *, int);

extern int lua_next (lua_State *L, int idx) {
  Table *t;
  int more;
  ((void) 0);
  ((void)L, ((void)0));
  t = gettable(L, idx);
  more = luaH_next(L, t, L->top - 1);
  if (more) {
    {L->top++; ((void)L, ((void)0));};
  }
  else
    L->top -= 1;
  ((void) 0);
  return more;
}
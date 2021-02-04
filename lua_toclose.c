
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



extern void luaF_newtbcupval(lua_State *, StkId);
extern StkId index2stack(lua_State *, int);

extern void lua_toclose (lua_State *L, int idx) {
  int nresults;
  StkId o;
  ((void) 0);
  o = index2stack(L, idx);
  nresults = L->ci->nresults;
  ((void)L, ((void)0));

  luaF_newtbcupval(L, o);
  if (!((nresults) < (-1)))
    L->ci->nresults = (-(nresults) - 3);
  ((void)0);
  ((void) 0);
}
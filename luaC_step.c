
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



extern void incstep(lua_State *, global_State *);
extern void genstep(lua_State *, global_State *);

void luaC_step (lua_State *L) {
  global_State *g = (L->l_G);
  ((void)0);
  if (g->gcrunning) {
    if((g->gckind == 1 || g->lastatomic != 0))
      genstep(L, g);
    else
      incstep(L, g);
  }
}
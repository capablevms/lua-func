
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



extern void luaE_setdebt(global_State *, l_mem);
extern void setpause(global_State *);
extern lu_mem singlestep(lua_State *);

extern void incstep (lua_State *L, global_State *g) {
  int stepmul = (((g->gcstepmul) * 4) | 1);
  l_mem debt = (g->GCdebt / sizeof(TValue)) * stepmul;
  l_mem stepsize = (g->gcstepsize <= (sizeof(l_mem) * 8 - 2))
                 ? ((((l_mem)(1)) << g->gcstepsize) / sizeof(TValue)) * stepmul
                 : ((l_mem)(((lu_mem)(~(lu_mem)0)) >> 1));
  do {
    lu_mem work = singlestep(L);
    debt -= work;
  } while (debt > -stepsize && g->gcstate != 8);
  if (g->gcstate == 8)
    setpause(g);
  else {
    debt = (debt / stepmul) * sizeof(TValue);
    luaE_setdebt(g, debt);
  }
}
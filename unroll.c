
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



extern void luaV_execute(lua_State *, CallInfo *);
extern void luaV_finishOp(lua_State *);
extern void finishCcall(lua_State *, int);
extern void finishCcall(lua_State *, int);

extern void unroll (lua_State *L, void *ud) {
  CallInfo *ci;
  if (ud != ((void*)0))
    finishCcall(L, *(int *)ud);
  while ((ci = L->ci) != &L->base_ci) {
    if (!(!((ci)->callstatus & (1<<1))))
      finishCcall(L, 1);
    else {
      luaV_finishOp(L);
      luaV_execute(L, ci);
    }
  }
}
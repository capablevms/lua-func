
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



extern void settraps(CallInfo *);

extern void lua_sethook (lua_State *L, lua_Hook func, int mask, int count) {
  if (func == ((void*)0) || mask == 0) {
    mask = 0;
    func = ((void*)0);
  }
  L->hook = func;
  L->basehookcount = count;
  (L->hookcount = L->basehookcount);
  L->hookmask = ((lu_byte)((mask)));
  if (mask)
    settraps(L->ci);
}

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



extern void luaM_free_(lua_State *, void *, size_t);
extern void luaE_freeCI(lua_State *);

static void freestack (lua_State *L) {
  if (L->stack == ((void*)0))
    return;
  L->ci = &L->base_ci;
  luaE_freeCI(L);
  ((void)0);
  luaM_free_(L, (L->stack), (((int)(((L)->stack_last - (L)->stack))) + 5)*sizeof(*(L->stack)));
}
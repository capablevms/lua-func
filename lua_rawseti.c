
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



extern void luaC_barrierback_(lua_State *, GCObject *);
extern void luaH_setint(lua_State *, Table *, lua_Integer, TValue *);
extern Table * gettable(lua_State *, int);

extern void lua_rawseti (lua_State *L, int idx, lua_Integer n) {
  Table *t;
  ((void) 0);
  ((void)L, ((void)0));
  t = gettable(L, idx);
  luaH_setint(L, t, n, (&(L->top - 1)->val));
  ( (((((&(L->top - 1)->val))->tt_) & (1 << 6)) && ((((&(((union GCUnion *)((t)))->gc)))->marked) & ((1<<(5)))) && (((((((&(L->top - 1)->val))->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrierback_(L,(&(((union GCUnion *)((t)))->gc))) : ((void)((0))));
  L->top--;
  ((void) 0);
}
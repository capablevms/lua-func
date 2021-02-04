
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

typedef struct LX {
  lu_byte extra_[LUA_EXTRASPACE];
  lua_State l;
} LX;

typedef struct LG {
  LX l;
  global_State g;
} LG;

extern void freestack(lua_State *);
extern void luaM_free_(lua_State *, void *, size_t);
extern void luaC_freeallobjects(lua_State *);
extern int luaF_close(lua_State *, StkId, int);

extern void close_state (lua_State *L) {
  global_State *g = (L->l_G);
  luaF_close(L, L->stack, (-2));
  luaC_freeallobjects(L);
  if ((((((((&g->nilvalue))->tt_)) & 0x0F)) == (0)))
    ((void)L);
  luaM_free_(L, ((L->l_G)->strt.hash), ((L->l_G)->strt.size)*sizeof(*((L->l_G)->strt.hash)));
  freestack(L);
  ((void)0);
  (*g->frealloc)(g->ud, (((LX *)(((lu_byte *)((L))) - __builtin_offsetof(LX, l)))), sizeof(LG), 0);
}
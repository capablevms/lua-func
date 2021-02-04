
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

extern void luaM_free_(lua_State *, void *, size_t);
extern void freestack(lua_State *);
extern int luaF_close(lua_State *, StkId, int);

void luaE_freethread (lua_State *L, lua_State *L1) {
  LX *l = (((LX *)(((lu_byte *)((L1))) - __builtin_offsetof(LX, l))));
  luaF_close(L1, L1->stack, (-1));
  ((void)0);
  ((void)L);
  freestack(L1);
  luaM_free_(L, (l), sizeof(*(l)));
}
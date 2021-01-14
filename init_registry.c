
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



extern void luaH_setint(lua_State *, Table *, lua_Integer, TValue *);
extern Table * luaH_new(lua_State *);
extern void luaH_setint(lua_State *, Table *, lua_Integer, TValue *);
extern void luaH_resize(lua_State *, Table *, unsigned int, unsigned int);
extern Table * luaH_new(lua_State *);

extern void init_registry (lua_State *L, global_State *g) {
  TValue temp;

  Table *registry = luaH_new(L);
  { TValue *io = (&g->l_registry); Table *x_ = (registry); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((((5) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
  luaH_resize(L, registry, 2, 0);

  { TValue *io = (&temp); lua_State *x_ = (L); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((((8) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
  luaH_setint(L, registry, 1, &temp);

  { TValue *io = (&temp); Table *x_ = (luaH_new(L)); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((((5) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
  luaH_setint(L, registry, 2, &temp);
}
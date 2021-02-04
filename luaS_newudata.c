
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



extern GCObject * luaC_newobj(lua_State *, int, size_t);
extern void luaM_toobig(lua_State *);
extern long __builtin_expect(long, long);

Udata *luaS_newudata (lua_State *L, size_t s, int nuvalue) {
  Udata *u;
  int i;
  GCObject *o;
  if ((__builtin_expect(((s > (sizeof(size_t) < sizeof(lua_Integer) ? ((size_t)(~(size_t)0)) : (size_t)(9223372036854775807LL)) - ((nuvalue) == 0 ? __builtin_offsetof(Udata0, bindata) : __builtin_offsetof(Udata, uv) + (sizeof(UValue) * (nuvalue)))) != 0), 0)))
    luaM_toobig(L);
  o = luaC_newobj(L, ((7) | ((0) << 4)), (((nuvalue) == 0 ? __builtin_offsetof(Udata0, bindata) : __builtin_offsetof(Udata, uv) + (sizeof(UValue) * (nuvalue))) + (s)));
  u = (&((((union GCUnion *)((o))))->u));
  u->len = s;
  u->nuvalue = nuvalue;
  u->metatable = ((void*)0);
  for (i = 0; i < nuvalue; i++)
    ((&u->uv[i].uv)->tt_=(((0) | ((0) << 4))));
  return u;
}
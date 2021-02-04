
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



extern void setnodevector(lua_State *, Table *, unsigned int);
extern GCObject * luaC_newobj(lua_State *, int, size_t);

Table *luaH_new (lua_State *L) {
  GCObject *o = luaC_newobj(L, ((5) | ((0) << 4)), sizeof(Table));
  Table *t = (&((((union GCUnion *)((o))))->h));
  t->metatable = ((void*)0);
  t->flags = ((lu_byte)(((~(~0u << (TM_EQ + 1))))));
  t->array = ((void*)0);
  t->alimit = 0;
  setnodevector(L, t, 0);
  return t;
}
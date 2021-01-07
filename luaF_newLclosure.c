
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

LClosure *luaF_newLclosure (lua_State *L, int nupvals) {
  GCObject *o = luaC_newobj(L, ((6) | ((0) << 4)), (((int)((__builtin_offsetof(LClosure, upvals)))) + ((int)((sizeof(TValue *)))) * (nupvals)));
  LClosure *c = (&((((union GCUnion *)((o))))->cl.l));
  c->p = ((void*)0);
  c->nupvalues = ((lu_byte)((nupvals)));
  while (nupvals--) c->upvals[nupvals] = ((void*)0);
  return c;
}
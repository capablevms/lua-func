
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



extern void luaC_barrier_(lua_State *, GCObject *, GCObject *);
extern GCObject * luaC_newobj(lua_State *, int, size_t);

void luaF_initupvals (lua_State *L, LClosure *cl) {
  int i;
  for (i = 0; i < cl->nupvalues; i++) {
    GCObject *o = luaC_newobj(L, ((9) | ((0) << 4)), sizeof(UpVal));
    UpVal *uv = (&((((union GCUnion *)((o))))->upv));
    uv->v = &uv->u.value;
    ((uv->v)->tt_=(((0) | ((0) << 4))));
    cl->upvals[i] = uv;
    ( ((((cl)->marked) & ((1<<(5)))) && (((uv)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(&(((union GCUnion *)((cl)))->gc)),(&(((union GCUnion *)((uv)))->gc))) : ((void)((0))));
  }
}
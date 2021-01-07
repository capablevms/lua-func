
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

Proto *luaF_newproto (lua_State *L) {
  GCObject *o = luaC_newobj(L, (((9 +1)) | ((0) << 4)), sizeof(Proto));
  Proto *f = (&((((union GCUnion *)((o))))->p));
  f->k = ((void*)0);
  f->sizek = 0;
  f->p = ((void*)0);
  f->sizep = 0;
  f->code = ((void*)0);
  f->sizecode = 0;
  f->lineinfo = ((void*)0);
  f->sizelineinfo = 0;
  f->abslineinfo = ((void*)0);
  f->sizeabslineinfo = 0;
  f->upvalues = ((void*)0);
  f->sizeupvalues = 0;
  f->numparams = 0;
  f->is_vararg = 0;
  f->maxstacksize = 0;
  f->locvars = ((void*)0);
  f->sizelocvars = 0;
  f->linedefined = 0;
  f->lastlinedefined = 0;
  f->source = ((void*)0);
  return f;
}
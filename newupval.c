
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

extern UpVal *newupval (lua_State *L, int tbc, StkId level, UpVal **prev) {
  GCObject *o = luaC_newobj(L, ((9) | ((0) << 4)), sizeof(UpVal));
  UpVal *uv = (&((((union GCUnion *)((o))))->upv));
  UpVal *next = *prev;
  uv->v = (&(level)->val);
  uv->tbc = tbc;
  uv->u.open.next = next;
  uv->u.open.previous = prev;
  if (next)
    next->u.open.previous = &uv->u.open.next;
  *prev = uv;
  if (!(L->twups != L)) {
    L->twups = (L->l_G)->twups;
    (L->l_G)->twups = L;
  }
  return uv;
}
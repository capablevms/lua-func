
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

extern void pushclosure (lua_State *L, Proto *p, UpVal **encup, StkId base,
                         StkId ra) {
  int nup = p->sizeupvalues;
  Upvaldesc *uv = p->upvalues;
  int i;
  LClosure *ncl = luaF_newLclosure(L, nup);
  ncl->p = p;
  { TValue *io = ((&(ra)->val)); LClosure *x_ = (ncl); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((((6) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
  for (i = 0; i < nup; i++) {
    if (uv[i].instack)
      ncl->upvals[i] = luaF_findupval(L, base + uv[i].idx);
    else
      ncl->upvals[i] = encup[uv[i].idx];
    ( ((((ncl)->marked) & ((1<<(5)))) && (((ncl->upvals[i])->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(&(((union GCUnion *)((ncl)))->gc)),(&(((union GCUnion *)((ncl->upvals[i])))->gc))) : ((void)((0))));
  }
}

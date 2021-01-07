
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
extern void luaF_unlinkupval(UpVal *);
extern int callclosemth(lua_State *, StkId, int);

int luaF_close (lua_State *L, StkId level, int status) {
  UpVal *uv;
  while ((uv = L->openupval) != ((void*)0) && (((StkId)((uv)->v))) >= level) {
    TValue *slot = &uv->u.value;
    ((void)0);
    if (uv->tbc && status != (-1)) {

      ptrdiff_t levelrel = ((char *)(level) - (char *)L->stack);
      status = callclosemth(L, (((StkId)((uv)->v))), status);
      level = ((StkId)((char *)L->stack + (levelrel)));
    }
    luaF_unlinkupval(uv);
    { TValue *io1=(slot); const TValue *io2=(uv->v); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
    uv->v = slot;
    if (!(((uv)->marked) & (((1<<(3)) | (1<<(4)))))) {
      ((((uv)->marked) |= ((1<<(5)))));
      ( ((((slot)->tt_) & (1 << 6)) && (((uv)->marked) & ((1<<(5)))) && ((((((slot)->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(&(((union GCUnion *)((uv)))->gc)),(((slot)->value_).gc)) : ((void)((0))));
    }
  }
  return status;
}
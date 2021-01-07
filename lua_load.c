
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
extern const TValue * luaH_getint(Table *, lua_Integer);
extern int luaD_protectedparser(lua_State *, ZIO *, const char *, const char *);
extern void luaZ_init(lua_State *, ZIO *, lua_Reader, void *);

extern int lua_load (lua_State *L, lua_Reader reader, void *data,
                      const char *chunkname, const char *mode) {
  ZIO z;
  int status;
  ((void) 0);
  if (!chunkname) chunkname = "?";
  luaZ_init(L, &z, reader, data);
  status = luaD_protectedparser(L, &z, chunkname, mode);
  if (status == 0) {
    LClosure *f = ((&((((union GCUnion *)(((((&(L->top - 1)->val))->value_).gc))))->cl.l)));
    if (f->nupvalues >= 1) {

      Table *reg = ((&((((union GCUnion *)((((&(L->l_G)->l_registry)->value_).gc))))->h)));
      const TValue *gt = luaH_getint(reg, 2);

      { TValue *io1=(f->upvals[0]->v); const TValue *io2=(gt); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
      ( ((((gt)->tt_) & (1 << 6)) && (((f->upvals[0])->marked) & ((1<<(5)))) && ((((((gt)->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(&(((union GCUnion *)((f->upvals[0])))->gc)),(((gt)->value_).gc)) : ((void)((0))));
    }
  }
  ((void) 0);
  return status;
}
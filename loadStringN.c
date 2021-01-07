
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

typedef struct {
  lua_State *L;
  ZIO *Z;
  const char *name;
} LoadState;


extern void luaC_barrier_(lua_State *, GCObject *, GCObject *);
extern void loadBlock(LoadState *, void *, size_t);
extern void luaD_inctop(lua_State *);
extern TString * luaS_createlngstrobj(lua_State *, size_t);
extern TString * luaS_newlstr(lua_State *, const char *, size_t);
extern void loadBlock(LoadState *, void *, size_t);
extern size_t loadSize(LoadState *);

static TString *loadStringN (LoadState *S, Proto *p) {
  lua_State *L = S->L;
  TString *ts;
  size_t size = loadSize(S);
  if (size == 0)
    return ((void*)0);
  else if (--size <= 40) {
    char buff[40];
    loadBlock(S,buff,(size)*sizeof((buff)[0]));
    ts = luaS_newlstr(L, buff, size);
  }
  else {
    ts = luaS_createlngstrobj(L, size);
    { TValue *io = ((&(L->top)->val)); TString *x_ = (ts); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((x_->tt) | (1 << 6)))); ((void)L, ((void)0)); };
    luaD_inctop(L);
    loadBlock(S,((ts)->contents),(size)*sizeof((((ts)->contents))[0]));
    L->top--;
  }
  ( ((((p)->marked) & ((1<<(5)))) && (((ts)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(&(((union GCUnion *)((p)))->gc)),(&(((union GCUnion *)((ts)))->gc))) : ((void)((0))));
  return ts;
}
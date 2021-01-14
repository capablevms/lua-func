
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


extern TString * loadString(LoadState *, Proto *);
extern lua_Integer loadInteger(LoadState *);
extern lua_Number loadNumber(LoadState *);
extern lu_byte loadByte(LoadState *);
extern void * luaM_malloc_(lua_State *, size_t, int);
extern void luaM_toobig(lua_State *);
extern int loadInt(LoadState *);

extern void loadConstants (LoadState *S, Proto *f) {
  int i;
  int n = loadInt(S);
  f->k = (((sizeof(n) >= sizeof(size_t) && ((size_t)(((n)))) + 1 > ((size_t)(~(size_t)0))/(sizeof(TValue))) ? luaM_toobig(S->L) : ((void)((0)))), ((TValue*)(luaM_malloc_(S->L, (n)*sizeof(TValue), 0))));
  f->sizek = n;
  for (i = 0; i < n; i++)
    ((&f->k[i])->tt_=(((0) | ((0) << 4))));
  for (i = 0; i < n; i++) {
    TValue *o = &f->k[i];
    int t = loadByte(S);
    switch (t) {
      case ((0) | ((0) << 4)):
        ((o)->tt_=(((0) | ((0) << 4))));
        break;
      case ((1) | ((0) << 4)):
        ((o)->tt_=(((1) | ((0) << 4))));
        break;
      case ((1) | ((1) << 4)):
        ((o)->tt_=(((1) | ((1) << 4))));
        break;
      case ((3) | ((1) << 4)):
        { TValue *io=(o); ((io)->value_).n=(loadNumber(S)); ((io)->tt_=(((3) | ((1) << 4)))); };
        break;
      case ((3) | ((0) << 4)):
        { TValue *io=(o); ((io)->value_).i=(loadInteger(S)); ((io)->tt_=(((3) | ((0) << 4)))); };
        break;
      case ((4) | ((0) << 4)):
      case ((4) | ((1) << 4)):
        { TValue *io = (o); TString *x_ = (loadString(S, f)); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((x_->tt) | (1 << 6)))); ((void)S->L, ((void)0)); };
        break;
      default: ((void)0);
    }
  }
}
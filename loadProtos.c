
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


extern void loadFunction(LoadState *, Proto *, TString *);
extern void luaC_barrier_(lua_State *, GCObject *, GCObject *);
extern Proto * luaF_newproto(lua_State *);
extern void * luaM_malloc_(lua_State *, size_t, int);
extern void luaM_toobig(lua_State *);
extern int loadInt(LoadState *);

static void loadProtos (LoadState *S, Proto *f) {
  int i;
  int n = loadInt(S);
  f->p = (((sizeof(n) >= sizeof(size_t) && ((size_t)(((n)))) + 1 > ((size_t)(~(size_t)0))/(sizeof(Proto *))) ? luaM_toobig(S->L) : ((void)((0)))), ((Proto **)(luaM_malloc_(S->L, (n)*sizeof(Proto *), 0))));
  f->sizep = n;
  for (i = 0; i < n; i++)
    f->p[i] = ((void*)0);
  for (i = 0; i < n; i++) {
    f->p[i] = luaF_newproto(S->L);
    ( ((((f)->marked) & ((1<<(5)))) && (((f->p[i])->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(S->L,(&(((union GCUnion *)((f)))->gc)),(&(((union GCUnion *)((f->p[i])))->gc))) : ((void)((0))));
    loadFunction(S, f->p[i], f->source);
  }
}
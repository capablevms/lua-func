
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


extern void loadBlock(LoadState *, void *, size_t);
extern void * luaM_malloc_(lua_State *, size_t, int);
extern void luaM_toobig(lua_State *);
extern int loadInt(LoadState *);

extern void loadCode (LoadState *S, Proto *f) {
  int n = loadInt(S);
  f->code = (((sizeof(n) >= sizeof(size_t) && ((size_t)(((n)))) + 1 > ((size_t)(~(size_t)0))/(sizeof(Instruction))) ? luaM_toobig(S->L) : ((void)((0)))), ((Instruction*)(luaM_malloc_(S->L, (n)*sizeof(Instruction), 0))));
  f->sizecode = n;
  loadBlock(S,f->code,(n)*sizeof((f->code)[0]));
}
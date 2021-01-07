
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
extern void luaD_inctop(lua_State *);
extern LClosure * luaF_newLclosure(lua_State *, int);
extern lu_byte loadByte(LoadState *);
extern void checkHeader(LoadState *);

LClosure *luaU_undump(lua_State *L, ZIO *Z, const char *name) {
  LoadState S;
  LClosure *cl;
  if (*name == '@' || *name == '=')
    S.name = name + 1;
  else if (*name == "\x1bLua"[0])
    S.name = "binary string";
  else
    S.name = name;
  S.L = L;
  S.Z = Z;
  checkHeader(&S);
  cl = luaF_newLclosure(L, loadByte(&S));
  { TValue *io = ((&(L->top)->val)); LClosure *x_ = (cl); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((((6) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
  luaD_inctop(L);
  cl->p = luaF_newproto(L);
  ( ((((cl)->marked) & ((1<<(5)))) && (((cl->p)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(&(((union GCUnion *)((cl)))->gc)),(&(((union GCUnion *)((cl->p)))->gc))) : ((void)((0))));
  loadFunction(&S, cl->p, ((void*)0));
  ((void)0);
                           ;
  return cl;
}
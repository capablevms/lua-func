
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

typedef struct BlockCnt {
  struct BlockCnt *previous;
  int firstlabel;
  int firstgoto;
  lu_byte nactvar;
  lu_byte upval;
  lu_byte isloop;
  lu_byte insidetbc;
} BlockCnt;


extern void mainfunc(LexState *, FuncState *);
extern void luaX_setinput(lua_State *, LexState *, ZIO *, TString *, int);
extern void luaC_barrier_(lua_State *, GCObject *, GCObject *);
extern TString * luaS_new(lua_State *, const char *);
extern void luaC_barrier_(lua_State *, GCObject *, GCObject *);
extern Proto * luaF_newproto(lua_State *);
extern void luaD_inctop(lua_State *);
extern Table * luaH_new(lua_State *);
extern void luaD_inctop(lua_State *);
extern LClosure * luaF_newLclosure(lua_State *, int);

LClosure *luaY_parser (lua_State *L, ZIO *z, Mbuffer *buff,
                       Dyndata *dyd, const char *name, int firstchar) {
  LexState lexstate;
  FuncState funcstate;
  LClosure *cl = luaF_newLclosure(L, 1);
  { TValue *io = ((&(L->top)->val)); LClosure *x_ = (cl); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((((6) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
  luaD_inctop(L);
  lexstate.h = luaH_new(L);
  { TValue *io = ((&(L->top)->val)); Table *x_ = (lexstate.h); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((((5) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
  luaD_inctop(L);
  funcstate.f = cl->p = luaF_newproto(L);
  ( ((((cl)->marked) & ((1<<(5)))) && (((cl->p)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(&(((union GCUnion *)((cl)))->gc)),(&(((union GCUnion *)((cl->p)))->gc))) : ((void)((0))));
  funcstate.f->source = luaS_new(L, name);
  ( ((((funcstate.f)->marked) & ((1<<(5)))) && (((funcstate.f->source)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(&(((union GCUnion *)((funcstate.f)))->gc)),(&(((union GCUnion *)((funcstate.f->source)))->gc))) : ((void)((0))));
  lexstate.buff = buff;
  lexstate.dyd = dyd;
  dyd->actvar.n = dyd->gt.n = dyd->label.n = 0;
  luaX_setinput(L, &lexstate, z, funcstate.f->source, firstchar);
  mainfunc(&lexstate, &funcstate);
  ((void)0);

  ((void)0);
  L->top--;
  return cl;
}
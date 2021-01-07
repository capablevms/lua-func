
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


extern void luaC_step(lua_State *);
extern void * luaM_shrinkvector_(lua_State *, void *, int *, int, int);
extern void * luaM_shrinkvector_(lua_State *, void *, int *, int, int);
extern void * luaM_shrinkvector_(lua_State *, void *, int *, int, int);
extern void * luaM_shrinkvector_(lua_State *, void *, int *, int, int);
extern void * luaM_shrinkvector_(lua_State *, void *, int *, int, int);
extern void * luaM_shrinkvector_(lua_State *, void *, int *, int, int);
extern void * luaM_shrinkvector_(lua_State *, void *, int *, int, int);
extern void luaK_finish(FuncState *);
extern void leaveblock(FuncState *);
extern void luaK_ret(FuncState *, int, int);
extern int luaY_nvarstack(FuncState *);

static void close_func (LexState *ls) {
  lua_State *L = ls->L;
  FuncState *fs = ls->fs;
  Proto *f = fs->f;
  luaK_ret(fs, luaY_nvarstack(fs), 0);
  leaveblock(fs);
  ((void)0);
  luaK_finish(fs);
  ((f->code)=((Instruction *)(luaM_shrinkvector_(L, f->code, &(f->sizecode), fs->pc, sizeof(Instruction)))));
  ((f->lineinfo)=((ls_byte *)(luaM_shrinkvector_(L, f->lineinfo, &(f->sizelineinfo), fs->pc, sizeof(ls_byte)))));
  ((f->abslineinfo)=((AbsLineInfo *)(luaM_shrinkvector_(L, f->abslineinfo, &(f->sizeabslineinfo), fs->nabslineinfo, sizeof(AbsLineInfo)))));

  ((f->k)=((TValue *)(luaM_shrinkvector_(L, f->k, &(f->sizek), fs->nk, sizeof(TValue)))));
  ((f->p)=((Proto * *)(luaM_shrinkvector_(L, f->p, &(f->sizep), fs->np, sizeof(Proto *)))));
  ((f->locvars)=((LocVar *)(luaM_shrinkvector_(L, f->locvars, &(f->sizelocvars), fs->ndebugvars, sizeof(LocVar)))));
  ((f->upvalues)=((Upvaldesc *)(luaM_shrinkvector_(L, f->upvalues, &(f->sizeupvalues), fs->nups, sizeof(Upvaldesc)))));
  ls->fs = fs->prev;
  { if ((L->l_G)->GCdebt > 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); };
}
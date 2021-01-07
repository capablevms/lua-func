
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
extern Vardesc * getlocalvardesc(FuncState *, int);
extern Upvaldesc * allocupvalue(FuncState *);

static int newupvalue (FuncState *fs, TString *name, expdesc *v) {
  Upvaldesc *up = allocupvalue(fs);
  FuncState *prev = fs->prev;
  if (v->k == VLOCAL) {
    up->instack = 1;
    up->idx = v->u.var.sidx;
    up->kind = getlocalvardesc(prev, v->u.var.vidx)->vd.kind;
    ((void)0);
  }
  else {
    up->instack = 0;
    up->idx = ((lu_byte)((v->u.info)));
    up->kind = prev->f->upvalues[v->u.info].kind;
    ((void)0);
  }
  up->name = name;
  ( ((((fs->f)->marked) & ((1<<(5)))) && (((name)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(fs->ls->L,(&(((union GCUnion *)((fs->f)))->gc)),(&(((union GCUnion *)((name)))->gc))) : ((void)((0))));
  return fs->nups - 1;
}
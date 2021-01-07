
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
extern Proto * luaF_newproto(lua_State *);
extern void * luaM_growaux_(lua_State *, void *, int, int *, int, int, const char *);

static Proto *addprototype (LexState *ls) {
  Proto *clp;
  lua_State *L = ls->L;
  FuncState *fs = ls->fs;
  Proto *f = fs->f;
  if (fs->np >= f->sizep) {
    int oldsize = f->sizep;
    ((f->p)=((Proto * *)(luaM_growaux_(L,f->p,fs->np,&(f->sizep),sizeof(Proto *), ((((size_t)((((1<<(8 + 8 + 1))-1)))) <= ((size_t)(~(size_t)0))/sizeof(Proto *)) ? (((1<<(8 + 8 + 1))-1)) : ((unsigned int)(((((size_t)(~(size_t)0))/sizeof(Proto *)))))),"functions"))));
    while (oldsize < f->sizep)
      f->p[oldsize++] = ((void*)0);
  }
  f->p[fs->np++] = clp = luaF_newproto(L);
  ( ((((f)->marked) & ((1<<(5)))) && (((clp)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(&(((union GCUnion *)((f)))->gc)),(&(((union GCUnion *)((clp)))->gc))) : ((void)((0))));
  return clp;
}
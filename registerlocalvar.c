
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
extern void * luaM_growaux_(lua_State *, void *, int, int *, int, int, const char *);

static int registerlocalvar (LexState *ls, FuncState *fs, TString *varname) {
  Proto *f = fs->f;
  int oldsize = f->sizelocvars;
  ((f->locvars)=((LocVar *)(luaM_growaux_(ls->L,f->locvars,fs->ndebugvars,&(f->sizelocvars),sizeof(LocVar), ((((size_t)((32767))) <= ((size_t)(~(size_t)0))/sizeof(LocVar)) ? (32767) : ((unsigned int)(((((size_t)(~(size_t)0))/sizeof(LocVar)))))),"local variables"))));

  while (oldsize < f->sizelocvars)
    f->locvars[oldsize++].varname = ((void*)0);
  f->locvars[fs->ndebugvars].varname = varname;
  f->locvars[fs->ndebugvars].startpc = fs->pc;
  ( ((((f)->marked) & ((1<<(5)))) && (((varname)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(ls->L,(&(((union GCUnion *)((f)))->gc)),(&(((union GCUnion *)((varname)))->gc))) : ((void)((0))));
  return fs->ndebugvars++;
}
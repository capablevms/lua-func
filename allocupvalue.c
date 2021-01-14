
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



extern void * luaM_growaux_(lua_State *, void *, int, int *, int, int, const char *);
extern void checklimit(FuncState *, int, int, const char *);

extern Upvaldesc *allocupvalue (FuncState *fs) {
  Proto *f = fs->f;
  int oldsize = f->sizeupvalues;
  checklimit(fs, fs->nups + 1, 255, "upvalues");
  ((f->upvalues)=((Upvaldesc *)(luaM_growaux_(fs->ls->L,f->upvalues,fs->nups,&(f->sizeupvalues),sizeof(Upvaldesc), ((((size_t)((255))) <= ((size_t)(~(size_t)0))/sizeof(Upvaldesc)) ? (255) : ((unsigned int)(((((size_t)(~(size_t)0))/sizeof(Upvaldesc)))))),"upvalues"))));

  while (oldsize < f->sizeupvalues)
    f->upvalues[oldsize++].name = ((void*)0);
  return &f->upvalues[fs->nups++];
}
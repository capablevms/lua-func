
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
extern int luaV_equalobj(lua_State *, const TValue *, const TValue *);
extern TValue * luaH_set(lua_State *, Table *, const TValue *);

static int addk (FuncState *fs, TValue *key, TValue *v) {
  lua_State *L = fs->ls->L;
  Proto *f = fs->f;
  TValue *idx = luaH_set(L, fs->ls->h, key);
  int k, oldsize;
  if (((((idx))->tt_) == (((3) | ((0) << 4))))) {
    k = ((int)(((((idx)->value_).i))));

    if (k < fs->nk && ((((&f->k[k])->tt_)) & 0x3F) == ((((v)->tt_)) & 0x3F) &&
                      luaV_equalobj(((void*)0),&f->k[k],v))
      return k;
  }

  oldsize = f->sizek;
  k = fs->nk;


  { TValue *io=(idx); ((io)->value_).i=(k); ((io)->tt_=(((3) | ((0) << 4)))); };
  ((f->k)=((TValue *)(luaM_growaux_(L,f->k,k,&(f->sizek),sizeof(TValue), ((((size_t)((((1<<((8 + 8 + 1) + 8))-1)))) <= ((size_t)(~(size_t)0))/sizeof(TValue)) ? (((1<<((8 + 8 + 1) + 8))-1)) : ((unsigned int)(((((size_t)(~(size_t)0))/sizeof(TValue)))))),"constants"))));
  while (oldsize < f->sizek) ((&f->k[oldsize++])->tt_=(((0) | ((0) << 4))));
  { TValue *io1=(&f->k[k]); const TValue *io2=(v); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
  fs->nk++;
  ( ((((v)->tt_) & (1 << 6)) && (((f)->marked) & ((1<<(5)))) && ((((((v)->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(&(((union GCUnion *)((f)))->gc)),(((v)->value_).gc)) : ((void)((0))));
  return k;
}
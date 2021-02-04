
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



extern void freehash(lua_State *, Table *);
extern void reinsert(lua_State *, Table *, Table *);
extern void exchangehashpart(Table *, Table *);
extern void luaD_throw(lua_State *, int);
extern void freehash(lua_State *, Table *);
extern long __builtin_expect(long, long);
extern void * luaM_realloc_(lua_State *, void *, size_t, size_t);
extern void exchangehashpart(Table *, Table *);
extern void luaH_setint(lua_State *, Table *, lua_Integer, TValue *);
extern void exchangehashpart(Table *, Table *);
extern void setnodevector(lua_State *, Table *, unsigned int);
extern unsigned int setlimittosize(Table *);

void luaH_resize (lua_State *L, Table *t, unsigned int newasize,
                                          unsigned int nhsize) {
  unsigned int i;
  Table newt;
  unsigned int oldasize = setlimittosize(t);
  TValue *newarray;

  setnodevector(L, &newt, nhsize);
  if (newasize < oldasize) {
    t->alimit = newasize;
    exchangehashpart(t, &newt);

    for (i = newasize; i < oldasize; i++) {
      if (!(((((((&t->array[i]))->tt_)) & 0x0F)) == (0)))
        luaH_setint(L, t, i + 1, &t->array[i]);
    }
    t->alimit = oldasize;
    exchangehashpart(t, &newt);
  }

  newarray = (((TValue *)(luaM_realloc_(L, t->array, ((size_t)((oldasize))) * sizeof(TValue), ((size_t)((newasize))) * sizeof(TValue)))));
  if ((__builtin_expect(((newarray == ((void*)0) && newasize > 0) != 0), 0))) {
    freehash(L, &newt);
    luaD_throw(L, 4);
  }

  exchangehashpart(t, &newt);
  t->array = newarray;
  t->alimit = newasize;
  for (i = oldasize; i < newasize; i++)
     ((&t->array[i])->tt_=(((0) | ((1) << 4))));

  reinsert(L, &newt, t);
  freehash(L, &newt);
}
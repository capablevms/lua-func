
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



extern void luaC_fix(lua_State *, GCObject *);
extern TString * luaS_newlstr(lua_State *, const char *, size_t);
extern void tablerehash(TString **, int, int);
extern void * luaM_malloc_(lua_State *, size_t, int);

void luaS_init (lua_State *L) {
  global_State *g = (L->l_G);
  int i, j;
  stringtable *tb = &(L->l_G)->strt;
  tb->hash = ((TString**)(luaM_malloc_(L, (128)*sizeof(TString*), 0)));
  tablerehash(tb->hash, 0, 128);
  tb->size = 128;

  g->memerrmsg = (luaS_newlstr(L, "" "not enough memory", (sizeof("not enough memory")/sizeof(char))-1));
  luaC_fix(L, (&(((union GCUnion *)((g->memerrmsg)))->gc)));
  for (i = 0; i < 53; i++)
    for (j = 0; j < 2; j++)
      g->strcache[i][j] = g->memerrmsg;
}
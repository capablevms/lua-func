
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



extern void * memcpy(void *restrict, const void *restrict, size_t);
extern TString * createstrobj(lua_State *, size_t, int, unsigned int);
extern void growstrtab(lua_State *, stringtable *);
extern int memcmp(const void *, const void *, size_t);
extern unsigned int luaS_hash(const char *, size_t, unsigned int);

extern TString *internshrstr (lua_State *L, const char *str, size_t l) {
  TString *ts;
  global_State *g = (L->l_G);
  stringtable *tb = &g->strt;
  unsigned int h = luaS_hash(str, l, g->seed);
  TString **list = &tb->hash[(((((int)(((h) & ((tb->size)-1)))))))];
  ((void)0);
  for (ts = *list; ts != ((void*)0); ts = ts->u.hnext) {
    if (l == ts->shrlen && (memcmp(str, ((ts)->contents), l * sizeof(char)) == 0)) {

      if ((((ts)->marked) & (((g)->currentwhite ^ ((1<<(3)) | (1<<(4)))))))
        ((ts)->marked ^= ((1<<(3)) | (1<<(4))));
      return ts;
    }
  }

  if (tb->nuse >= tb->size) {
    growstrtab(L, tb);
    list = &tb->hash[(((((int)(((h) & ((tb->size)-1)))))))];
  }
  ts = createstrobj(L, l, ((4) | ((0) << 4)), h);
  memcpy(((ts)->contents), str, l * sizeof(char));
  ts->shrlen = ((lu_byte)((l)));
  ts->u.hnext = *list;
  *list = ts;
  tb->nuse++;
  return ts;
}
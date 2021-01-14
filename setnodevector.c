
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

extern const Node dummynode_;

extern void * luaM_malloc_(lua_State *, size_t, int);
extern void luaG_runerror(lua_State *, const char *, ...);
extern int luaO_ceillog2(unsigned int);

extern void setnodevector (lua_State *L, Table *t, unsigned int size) {
  if (size == 0) {
    t->node = ((Node *)((&dummynode_)));
    t->lsizenode = 0;
    t->lastfree = ((void*)0);
  }
  else {
    int i;
    int lsize = luaO_ceillog2(size);
    if (lsize > (((int)((sizeof(int) * 8 - 1))) - 1) || (1u << lsize) > ((((size_t)((1u << (((int)((sizeof(int) * 8 - 1))) - 1)))) <= ((size_t)(~(size_t)0))/sizeof(Node)) ? (1u << (((int)((sizeof(int) * 8 - 1))) - 1)) : ((unsigned int)(((((size_t)(~(size_t)0))/sizeof(Node)))))))
      luaG_runerror(L, "table overflow");
    size = (1<<(lsize));
    t->node = ((Node*)(luaM_malloc_(L, (size)*sizeof(Node), 0)));
    for (i = 0; i < (int)size; i++) {
      Node *n = (&(t)->node[i]);
      ((n)->u.next) = 0;
      (((n)->u.key_tt) = 0);
      (((&(n)->i_val))->tt_=(((0) | ((1) << 4))));
    }
    t->lsizenode = ((lu_byte)((lsize)));
    t->lastfree = (&(t)->node[size]);
  }
}
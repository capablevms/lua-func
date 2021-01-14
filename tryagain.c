
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



extern void luaC_fullgc(lua_State *, int);

extern void *tryagain (lua_State *L, void *block,
                       size_t osize, size_t nsize) {
  global_State *g = (L->l_G);
  if ((((((((&g->nilvalue))->tt_)) & 0x0F)) == (0))) {
    luaC_fullgc(L, 1);
    return (*g->frealloc)(g->ud, block, osize, nsize);
  }
  else return ((void*)0);
}
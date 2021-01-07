
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



extern void luaE_shrinkCI(lua_State *);
extern int luaD_reallocstack(lua_State *, int, int);
extern int stackinuse(lua_State *);

void luaD_shrinkstack (lua_State *L) {
  int inuse = stackinuse(L);
  int nsize = inuse * 2;
  int max = inuse * 3;
  if (max > 1000000) {
    max = 1000000;
    if (nsize > 1000000)
      nsize = 1000000;
  }


  if (inuse <= 1000000 && ((int)(((L)->stack_last - (L)->stack))) > max)
    luaD_reallocstack(L, nsize, 0);
  else
    ((void)0);
  luaE_shrinkCI(L);
}
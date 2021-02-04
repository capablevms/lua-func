
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



extern void luaS_resize(lua_State *, int);
extern void luaD_throw(lua_State *, int);
extern void luaC_fullgc(lua_State *, int);
extern long __builtin_expect(long, long);

extern void growstrtab (lua_State *L, stringtable *tb) {
  if ((__builtin_expect(((tb->nuse == 2147483647) != 0), 0))) {
    luaC_fullgc(L, 1);
    if (tb->nuse == 2147483647)
      luaD_throw(L, 4);
  }
  if (tb->size <= ((int)((((((size_t)((2147483647))) <= ((size_t)(~(size_t)0))/sizeof(TString*)) ? (2147483647) : ((unsigned int)(((((size_t)(~(size_t)0))/sizeof(TString*))))))))) / 2)
    luaS_resize(L, tb->size * 2);
}
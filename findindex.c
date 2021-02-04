
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



extern void luaG_runerror(lua_State *, const char *, ...);
extern long __builtin_expect(long, long);
extern const TValue * getgeneric(Table *, const TValue *, int);
extern unsigned int arrayindex(lua_Integer);

extern unsigned int findindex (lua_State *L, Table *t, TValue *key,
                               unsigned int asize) {
  unsigned int i;
  if ((((((((key))->tt_)) & 0x0F)) == (0))) return 0;
  i = ((((key))->tt_) == (((3) | ((0) << 4)))) ? arrayindex((((key)->value_).i)) : 0;
  if (i - 1u < asize)
    return i;
  else {
    const TValue *n = getgeneric(t, key, 1);
    if ((__builtin_expect(((((((n))->tt_) == (((0) | ((2) << 4))))) != 0), 0)))
      luaG_runerror(L, "invalid key to 'next'");
    i = ((int)((((Node *)((n))) - (&(t)->node[0]))));

    return (i + 1) + asize;
  }
}
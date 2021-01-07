
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
extern int luaD_reallocstack(lua_State *, int, int);
extern int luaD_reallocstack(lua_State *, int, int);
extern long __builtin_expect(long, long);
extern void luaD_throw(lua_State *, int);
extern long __builtin_expect(long, long);

int luaD_growstack (lua_State *L, int n, int raiseerror) {
  int size = ((int)(((L)->stack_last - (L)->stack)));
  if ((__builtin_expect(((size > 1000000) != 0), 0))) {



    ((void)0);
    if (raiseerror)
      luaD_throw(L, 5);
    return 0;
  }
  else {
    int newsize = 2 * size;
    int needed = ((int)((L->top - L->stack))) + n;
    if (newsize > 1000000)
      newsize = 1000000;
    if (newsize < needed)
      newsize = needed;
    if ((__builtin_expect(((newsize <= 1000000) != 0), 1)))
      return luaD_reallocstack(L, newsize, raiseerror);
    else {

      luaD_reallocstack(L, (1000000 + 200), raiseerror);
      if (raiseerror)
        luaG_runerror(L, "stack overflow");
      return 0;
    }
  }
}
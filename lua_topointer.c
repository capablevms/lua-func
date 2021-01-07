
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



extern void * touserdata(const TValue *);
extern TValue * index2value(lua_State *, int);

extern const void *lua_topointer (lua_State *L, int idx) {
  const TValue *o = index2value(L, idx);
  switch (((((o)->tt_)) & 0x3F)) {
    case ((6) | ((1) << 4)): return ((void *)((((size_t)(((((o)->value_).f)))))));
    case ((7) | ((0) << 4)): case ((2) | ((0) << 4)):
      return touserdata(o);
    default: {
      if ((((o)->tt_) & (1 << 6)))
        return (((o)->value_).gc);
      else
        return ((void*)0);
    }
  }
}
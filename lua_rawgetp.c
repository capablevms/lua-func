
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



extern int finishrawget(lua_State *, const TValue *);
extern const TValue * luaH_get(Table *, const TValue *);
extern Table * gettable(lua_State *, int);

extern int lua_rawgetp (lua_State *L, int idx, const void *p) {
  Table *t;
  TValue k;
  ((void) 0);
  t = gettable(L, idx);
  { TValue *io=(&k); ((io)->value_).p=(((void *)((p)))); ((io)->tt_=(((2) | ((0) << 4)))); };
  return finishrawget(L, luaH_get(t, &k));
}
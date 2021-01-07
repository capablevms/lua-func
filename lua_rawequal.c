
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



extern int luaV_equalobj(lua_State *, const TValue *, const TValue *);
extern TValue * index2value(lua_State *, int);
extern TValue * index2value(lua_State *, int);

extern int lua_rawequal (lua_State *L, int index1, int index2) {
  const TValue *o1 = index2value(L, index1);
  const TValue *o2 = index2value(L, index2);
  return ((!(((((((o1))->tt_)) & 0x0F)) == (0)) || o1 != &(L->l_G)->nilvalue) && (!(((((((o2))->tt_)) & 0x0F)) == (0)) || o2 != &(L->l_G)->nilvalue)) ? luaV_equalobj(((void*)0),o1,o2) : 0;
}
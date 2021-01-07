
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



extern lua_Unsigned luaH_getn(Table *);
extern TValue * index2value(lua_State *, int);

extern lua_Unsigned lua_rawlen (lua_State *L, int idx) {
  const TValue *o = index2value(L, idx);
  switch (((((o)->tt_)) & 0x3F)) {
    case ((4) | ((0) << 4)): return ((&((((union GCUnion *)((((o)->value_).gc))))->ts)))->shrlen;
    case ((4) | ((1) << 4)): return ((&((((union GCUnion *)((((o)->value_).gc))))->ts)))->u.lnglen;
    case ((7) | ((0) << 4)): return ((&((((union GCUnion *)((((o)->value_).gc))))->u)))->len;
    case ((5) | ((0) << 4)): return luaH_getn(((&((((union GCUnion *)((((o)->value_).gc))))->h))));
    default: return 0;
  }
}
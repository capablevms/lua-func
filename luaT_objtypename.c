
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



extern const TValue * luaH_getshortstr(Table *, TString *);
extern TString * luaS_new(lua_State *, const char *);

const char *luaT_objtypename (lua_State *L, const TValue *o) {
  Table *mt;
  if ((((((o))->tt_) == (((((5) | ((0) << 4))) | (1 << 6)))) && (mt = ((&((((union GCUnion *)((((o)->value_).gc))))->h)))->metatable) != ((void*)0)) ||
      (((((o))->tt_) == (((((7) | ((0) << 4))) | (1 << 6)))) && (mt = ((&((((union GCUnion *)((((o)->value_).gc))))->u)))->metatable) != ((void*)0))) {
    const TValue *name = luaH_getshortstr(mt, luaS_new(L, "__name"));
    if ((((((((name))->tt_)) & 0x0F)) == (4)))
      return ((((&((((union GCUnion *)((((name)->value_).gc))))->ts))))->contents);
  }
  return luaT_typenames_[((((((o)->tt_)) & 0x0F))) + 1];
}
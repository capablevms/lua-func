
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



extern TValue * index2value(lua_State *, int);
extern void luaC_step(lua_State *);
extern void luaO_tostring(lua_State *, TValue *);
extern TValue * index2value(lua_State *, int);

extern const char *lua_tolstring (lua_State *L, int idx, size_t *len) {
  TValue *o;
  ((void) 0);
  o = index2value(L, idx);
  if (!(((((((o))->tt_)) & 0x0F)) == (4))) {
    if (!(((((((o))->tt_)) & 0x0F)) == (3))) {
      if (len != ((void*)0)) *len = 0;
      ((void) 0);
      return ((void*)0);
    }
    luaO_tostring(L, o);
    { if ((L->l_G)->GCdebt > 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); };
    o = index2value(L, idx);
  }
  if (len != ((void*)0))
    *len = ((((&((((union GCUnion *)((((o)->value_).gc))))->ts))))->tt == ((4) | ((0) << 4)) ? (((&((((union GCUnion *)((((o)->value_).gc))))->ts))))->shrlen : (((&((((union GCUnion *)((((o)->value_).gc))))->ts))))->u.lnglen);
  ((void) 0);
  return ((((&((((union GCUnion *)((((o)->value_).gc))))->ts))))->contents);
}
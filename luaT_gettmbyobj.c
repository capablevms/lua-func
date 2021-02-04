
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

const TValue *luaT_gettmbyobj (lua_State *L, const TValue *o, TMS event) {
  Table *mt;
  switch ((((((o)->tt_)) & 0x0F))) {
    case 5:
      mt = ((&((((union GCUnion *)((((o)->value_).gc))))->h)))->metatable;
      break;
    case 7:
      mt = ((&((((union GCUnion *)((((o)->value_).gc))))->u)))->metatable;
      break;
    default:
      mt = (L->l_G)->mt[(((((o)->tt_)) & 0x0F))];
  }
  return (mt ? luaH_getshortstr(mt, (L->l_G)->tmname[event]) : &(L->l_G)->nilvalue);
}
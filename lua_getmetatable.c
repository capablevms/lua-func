
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

extern int lua_getmetatable (lua_State *L, int objindex) {
  const TValue *obj;
  Table *mt;
  int res = 0;
  ((void) 0);
  obj = index2value(L, objindex);
  switch ((((((obj)->tt_)) & 0x0F))) {
    case 5:
      mt = ((&((((union GCUnion *)((((obj)->value_).gc))))->h)))->metatable;
      break;
    case 7:
      mt = ((&((((union GCUnion *)((((obj)->value_).gc))))->u)))->metatable;
      break;
    default:
      mt = (L->l_G)->mt[(((((obj)->tt_)) & 0x0F))];
      break;
  }
  if (mt != ((void*)0)) {
    { TValue *io = ((&(L->top)->val)); Table *x_ = (mt); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((((5) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
    {L->top++; ((void)L, ((void)0));};
    res = 1;
  }
  ((void) 0);
  return res;
}
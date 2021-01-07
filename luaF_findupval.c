
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



extern UpVal * newupval(lua_State *, int, StkId, UpVal **);

UpVal *luaF_findupval (lua_State *L, StkId level) {
  UpVal **pp = &L->openupval;
  UpVal *p;
  ((void)0);
  while ((p = *pp) != ((void*)0) && (((StkId)((p)->v))) >= level) {
    ((void)0);
    if ((((StkId)((p)->v))) == level)
      return p;
    pp = &p->u.open.next;
  }

  return newupval(L, 0, level, pp);
}
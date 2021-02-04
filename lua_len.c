
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



extern void luaV_objlen(lua_State *, StkId, const TValue *);
extern TValue * index2value(lua_State *, int);

extern void lua_len (lua_State *L, int idx) {
  TValue *t;
  ((void) 0);
  t = index2value(L, idx);
  luaV_objlen(L, L->top, t);
  {L->top++; ((void)L, ((void)0));};
  ((void) 0);
}
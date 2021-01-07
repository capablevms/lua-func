
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

typedef struct UBox {
  void *box;
  size_t bsize;
} UBox;


extern int lua_setmetatable(lua_State *, int);
extern void luaL_setfuncs(lua_State *, const luaL_Reg *, int);
extern int luaL_newmetatable(lua_State *, const char *);
extern void * lua_newuserdatauv(lua_State *, size_t, int);

static void newbox (lua_State *L) {
  UBox *box = (UBox *)lua_newuserdatauv(L, sizeof(UBox), 0);
  box->box = ((void*)0);
  box->bsize = 0;
  if (luaL_newmetatable(L, "_UBOX*"))
    luaL_setfuncs(L, boxmt, 0);
  lua_setmetatable(L, -2);
}
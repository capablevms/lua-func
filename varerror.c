
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



extern void luaG_runerror(lua_State *, const char *, ...);
extern const char * luaG_findlocal(lua_State *, CallInfo *, int, StkId *);

static void varerror (lua_State *L, StkId level, const char *msg) {
  int idx = ((int)((level - L->ci->func)));
  const char *vname = luaG_findlocal(L, L->ci, idx, ((void*)0));
  if (vname == ((void*)0)) vname = "?";
  luaG_runerror(L, msg, vname);
}
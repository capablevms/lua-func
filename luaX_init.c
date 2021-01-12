
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

extern const char *const luaX_tokens[];

extern void luaC_fix(lua_State *, GCObject *);
extern TString * luaS_new(lua_State *, const char *);
extern void luaC_fix(lua_State *, GCObject *);
extern TString * luaS_newlstr(lua_State *, const char *, size_t);

void luaX_init (lua_State *L) {
  int i;
  TString *e = (luaS_newlstr(L, "" "_ENV", (sizeof("_ENV")/sizeof(char))-1));
  luaC_fix(L, (&(((union GCUnion *)((e)))->gc)));
  for (i=0; i<(((int)((TK_WHILE-((127*2 +1) + 1) + 1)))); i++) {
    TString *ts = luaS_new(L, luaX_tokens[i]);
    luaC_fix(L, (&(((union GCUnion *)((ts)))->gc)));
    ts->extra = ((lu_byte)((i+1)));
  }
}
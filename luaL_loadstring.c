
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

typedef struct LoadS {
  const char *s;
  size_t size;
} LoadS;


extern int luaL_loadbufferx(lua_State *, const char *, size_t, const char *, const char *);
extern unsigned long strlen(const char *);

extern int luaL_loadstring (lua_State *L, const char *s) {
  return luaL_loadbufferx(L,s,strlen(s),s,((void*)0));
}
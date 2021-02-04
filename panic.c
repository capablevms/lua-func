
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



extern int fflush(FILE *);
extern int fprintf(FILE *restrict, const char *restrict, ...);
extern const char * lua_tolstring(lua_State *, int, size_t *);

extern int panic (lua_State *L) {
  const char *msg = lua_tolstring(L, (-1), ((void*)0));
  if (msg == ((void*)0)) msg = "error object is not a string";
  (fprintf(stderr, ("PANIC: unprotected error in call to Lua API (%s)\n"), (msg)), fflush(stderr));

  return 0;
}
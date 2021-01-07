
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
extern unsigned long fwrite(const void *restrict, size_t, size_t, FILE *restrict);
extern void lua_settop(lua_State *, int);
extern unsigned long fwrite(const void *restrict, size_t, size_t, FILE *restrict);
extern unsigned long fwrite(const void *restrict, size_t, size_t, FILE *restrict);
extern const char * luaL_tolstring(lua_State *, int, size_t *);
extern int lua_gettop(lua_State *);

static int luaB_print (lua_State *L) {
  int n = lua_gettop(L);
  int i;
  for (i = 1; i <= n; i++) {
    size_t l;
    const char *s = luaL_tolstring(L, i, &l);
    if (i > 1)
      fwrite(("\t"), sizeof(char), (1), stdout);
    fwrite((s), sizeof(char), (l), stdout);
    lua_settop(L, -(1)-1);
  }
  (fwrite(("\n"), sizeof(char), (1), stdout), fflush(stdout));
  return 0;
}
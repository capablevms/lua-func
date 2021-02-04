
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

typedef luaL_Stream LStream;


extern int lua_getfield(lua_State *, int, const char *);
extern void lua_setfield(lua_State *, int, const char *);
extern void lua_pushvalue(lua_State *, int);
extern FILE * tofile(lua_State *);
extern void opencheck(lua_State *, const char *, const char *);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern int lua_type(lua_State *, int);

extern int g_iofile (lua_State *L, const char *f, const char *mode) {
  if (!(lua_type(L, (1)) <= 0)) {
    const char *filename = lua_tolstring(L, (1), ((void*)0));
    if (filename)
      opencheck(L, filename, mode);
    else {
      tofile(L);
      lua_pushvalue(L, 1);
    }
    lua_setfield(L, (-1000000 - 1000), f);
  }

  lua_getfield(L, (-1000000 - 1000), f);
  return 1;
}
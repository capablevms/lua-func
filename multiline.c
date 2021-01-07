
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



extern void lua_concat(lua_State *, int);
extern void lua_rotate(lua_State *, int, int);
extern const char * lua_pushstring(lua_State *, const char *);
extern int pushline(lua_State *, int);
extern int incomplete(lua_State *, int);
extern int luaL_loadbufferx(lua_State *, const char *, size_t, const char *, const char *);
extern const char * lua_tolstring(lua_State *, int, size_t *);

static int multiline (lua_State *L) {
  for (;;) {
    size_t len;
    const char *line = lua_tolstring(L, 1, &len);
    int status = luaL_loadbufferx(L,line,len,"=stdin",((void*)0));
    if (!incomplete(L, status) || !pushline(L, 0)) {
      { (void)L; (void)line; };
      return status;
    }
    lua_pushstring(L, "" "\n");
    lua_rotate(L, (-2), 1);
    lua_concat(L, 3);
  }
}
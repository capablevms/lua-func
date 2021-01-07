
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



extern void lua_settop(lua_State *, int);
extern void lua_settop(lua_State *, int);
extern void lua_rotate(lua_State *, int, int);
extern int luaL_loadbufferx(lua_State *, const char *, size_t, const char *, const char *);
extern unsigned long strlen(const char *);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern const char * lua_tolstring(lua_State *, int, size_t *);

static int addreturn (lua_State *L) {
  const char *line = lua_tolstring(L, (-1), ((void*)0));
  const char *retline = lua_pushfstring(L, "return %s;", line);
  int status = luaL_loadbufferx(L,retline,strlen(retline),"=stdin",((void*)0));
  if (status == 0) {
    (lua_rotate(L, (-2), -1), lua_settop(L, -(1)-1));
    if (line[0] != '\0')
      { (void)L; (void)line; };
  }
  else
    lua_settop(L, -(2)-1);
  return status;
}
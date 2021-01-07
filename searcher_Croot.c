
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



extern const char * lua_pushstring(lua_State *, const char *);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern int checkload(lua_State *, int, const char *);
extern int loadfunc(lua_State *, const char *, const char *);
extern const char * findfile(lua_State *, const char *, const char *, const char *);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern const char * lua_pushlstring(lua_State *, const char *, size_t);
extern char * strchr(const char *, int);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

static int searcher_Croot (lua_State *L) {
  const char *filename;
  const char *name = (luaL_checklstring(L, (1), ((void*)0)));
  const char *p = strchr(name, '.');
  int stat;
  if (p == ((void*)0)) return 0;
  lua_pushlstring(L, name, p - name);
  filename = findfile(L, lua_tolstring(L, (-1), ((void*)0)), "cpath", "/");
  if (filename == ((void*)0)) return 1;
  if ((stat = loadfunc(L, filename, name)) != 0) {
    if (stat != 2)
      return checkload(L, 0, filename);
    else {
      lua_pushfstring(L, "no module '%s' in file '%s'", name, filename);
      return 1;
    }
  }
  lua_pushstring(L, filename);
  return 2;
}
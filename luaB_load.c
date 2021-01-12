
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



extern int load_aux(lua_State *, int, int);
extern int lua_load(lua_State *, lua_Reader, void *, const char *, const char *);
extern void lua_settop(lua_State *, int);
extern void luaL_checktype(lua_State *, int, int);
extern const char * luaL_optlstring(lua_State *, int, const char *, size_t *);
extern int luaL_loadbufferx(lua_State *, const char *, size_t, const char *, const char *);
extern const char * luaL_optlstring(lua_State *, int, const char *, size_t *);
extern int lua_type(lua_State *, int);
extern const char * luaL_optlstring(lua_State *, int, const char *, size_t *);
extern const char * lua_tolstring(lua_State *, int, size_t *);

extern const char *generic_reader (lua_State *, void *, size_t *);

static int luaB_load (lua_State *L) {
  int status;
  size_t l;
  const char *s = lua_tolstring(L, 1, &l);
  const char *mode = (luaL_optlstring(L, (3), ("bt"), ((void*)0)));
  int env = (!(lua_type(L, (4)) == (-1)) ? 4 : 0);
  if (s != ((void*)0)) {
    const char *chunkname = (luaL_optlstring(L, (2), (s), ((void*)0)));
    status = luaL_loadbufferx(L, s, l, chunkname, mode);
  }
  else {
    const char *chunkname = (luaL_optlstring(L, (2), ("=(load)"), ((void*)0)));
    luaL_checktype(L, 1, 6);
    lua_settop(L, 5);
    status = lua_load(L, generic_reader, ((void*)0), chunkname, mode);
  }
  return load_aux(L, status, env);
}
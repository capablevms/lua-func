
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
extern void lua_setfield(lua_State *, int, const char *);
extern void luaL_pushresult(luaL_Buffer *);
extern void luaL_addlstring(luaL_Buffer *, const char *, size_t);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern void luaL_addstring(luaL_Buffer *, const char *);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern void luaL_addlstring(luaL_Buffer *, const char *, size_t);
extern void luaL_buffinit(lua_State *, luaL_Buffer *);
extern unsigned long strlen(const char *);
extern const char * lua_pushstring(lua_State *, const char *);
extern char * strstr(const char *, const char *);
extern const char * lua_pushstring(lua_State *, const char *);
extern int noenv(lua_State *);
extern char * getenv(const char *);
extern char * getenv(const char *);
extern const char * lua_pushfstring(lua_State *, const char *, ...);

extern void setpath (lua_State *L, const char *fieldname,
                                   const char *envname,
                                   const char *dft) {
  const char *dftmark;
  const char *nver = lua_pushfstring(L, "%s%s", envname, "_" "5" "_" "4");
  const char *path = getenv(nver);
  if (path == ((void*)0))
    path = getenv(envname);
  if (path == ((void*)0) || noenv(L))
    lua_pushstring(L, dft);
  else if ((dftmark = strstr(path, ";" ";")) == ((void*)0))
    lua_pushstring(L, path);
  else {
    size_t len = strlen(path);
    luaL_Buffer b;
    luaL_buffinit(L, &b);
    if (path < dftmark) {
      luaL_addlstring(&b, path, dftmark - path);
      ((void)((&b)->n < (&b)->size || luaL_prepbuffsize((&b), 1)), ((&b)->b[(&b)->n++] = (*";")));
    }
    luaL_addstring(&b, dft);
    if (dftmark < path + len - 2) {
      ((void)((&b)->n < (&b)->size || luaL_prepbuffsize((&b), 1)), ((&b)->b[(&b)->n++] = (*";")));
      luaL_addlstring(&b, dftmark + 2, (path + len - 2) - dftmark);
    }
    luaL_pushresult(&b);
  }
  ((void)0);
  lua_setfield(L, -3, fieldname);
  lua_settop(L, -(1)-1);
}
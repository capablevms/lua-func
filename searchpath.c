
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



extern void pusherrornotfound(lua_State *, const char *);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern void luaL_pushresult(luaL_Buffer *);
extern const char * lua_pushstring(lua_State *, const char *);
extern int readable(const char *);
extern const char * getnextfilename(char **, char *);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern void luaL_addgsub(luaL_Buffer *, const char *, const char *, const char *);
extern void luaL_buffinit(lua_State *, luaL_Buffer *);
extern const char * luaL_gsub(lua_State *, const char *, const char *, const char *);
extern char * strchr(const char *, int);

static const char *searchpath (lua_State *L, const char *name,
                                             const char *path,
                                             const char *sep,
                                             const char *dirsep) {
  luaL_Buffer buff;
  char *pathname;
  char *endpathname;
  const char *filename;

  if (*sep != '\0' && strchr(name, *sep) != ((void*)0))
    name = luaL_gsub(L, name, sep, dirsep);
  luaL_buffinit(L, &buff);

  luaL_addgsub(&buff, path, "?", name);
  ((void)((&buff)->n < (&buff)->size || luaL_prepbuffsize((&buff), 1)), ((&buff)->b[(&buff)->n++] = ('\0')));
  pathname = ((&buff)->b);
  endpathname = pathname + ((&buff)->n) - 1;
  while ((filename = getnextfilename(&pathname, endpathname)) != ((void*)0)) {
    if (readable(filename))
      return lua_pushstring(L, filename);
  }
  luaL_pushresult(&buff);
  pusherrornotfound(L, lua_tolstring(L, (-1), ((void*)0)));
  return ((void*)0);
}
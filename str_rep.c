
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



extern void luaL_pushresultsize(luaL_Buffer *, size_t);
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern char * luaL_buffinitsize(lua_State *, luaL_Buffer *, size_t);
extern int luaL_error(lua_State *, const char *, ...);
extern const char * lua_pushstring(lua_State *, const char *);
extern const char * luaL_optlstring(lua_State *, int, const char *, size_t *);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

extern int str_rep (lua_State *L) {
  size_t l, lsep;
  const char *s = luaL_checklstring(L, 1, &l);
  lua_Integer n = luaL_checkinteger(L, 2);
  const char *sep = luaL_optlstring(L, 3, "", &lsep);
  if (n <= 0) lua_pushstring(L, "" "");
  else if (l + lsep < l || l + lsep > (sizeof(size_t) < sizeof(int) ? ((size_t)(~(size_t)0)) : (size_t)(2147483647)) / n)
    return luaL_error(L, "resulting string too large");
  else {
    size_t totallen = (size_t)n * l + (size_t)(n - 1) * lsep;
    luaL_Buffer b;
    char *p = luaL_buffinitsize(L, &b, totallen);
    while (n-- > 1) {
      memcpy(p, s, l * sizeof(char)); p += l;
      if (lsep > 0) {
        memcpy(p, sep, lsep * sizeof(char));
        p += lsep;
      }
    }
    memcpy(p, s, l * sizeof(char));
    luaL_pushresultsize(&b, totallen);
  }
  return 1;
}
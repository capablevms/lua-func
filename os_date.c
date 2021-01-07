
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



extern void luaL_pushresult(luaL_Buffer *);
extern size_t strftime(char *restrict, size_t, const char *restrict, const struct tm *restrict);
extern const char * checkoption(lua_State *, const char *, ptrdiff_t, char *);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern void luaL_buffinit(lua_State *, luaL_Buffer *);
extern void setallfields(lua_State *, struct tm *);
extern void lua_createtable(lua_State *, int, int);
extern int strcmp(const char *, const char *);
extern int luaL_error(lua_State *, const char *, ...);
extern struct tm * localtime(const time_t *);
extern struct tm * gmtime(const time_t *);
extern time_t l_checktime(lua_State *, int);
extern time_t time(time_t *);
extern int lua_type(lua_State *, int);
extern const char * luaL_optlstring(lua_State *, int, const char *, size_t *);

static int os_date (lua_State *L) {
  size_t slen;
  const char *s = luaL_optlstring(L, 1, "%c", &slen);
  time_t t = ((lua_type(L, ((2))) <= 0) ? (time(((void*)0))) : l_checktime(L,(2)));
  const char *se = s + slen;
  struct tm tmr, *stm;
  if (*s == '!') {
    stm = ((void)(&tmr)->tm_sec, gmtime(&t));
    s++;
  }
  else
    stm = ((void)(&tmr)->tm_sec, localtime(&t));
  if (stm == ((void*)0))
    return luaL_error(L,
                 "date result cannot be represented in this installation");
  if (strcmp(s, "*t") == 0) {
    lua_createtable(L, 0, 9);
    setallfields(L, stm);
  }
  else {
    char cc[4];
    luaL_Buffer b;
    cc[0] = '%';
    luaL_buffinit(L, &b);
    while (s < se) {
      if (*s != '%')
        ((void)((&b)->n < (&b)->size || luaL_prepbuffsize((&b), 1)), ((&b)->b[(&b)->n++] = (*s++)));
      else {
        size_t reslen;
        char *buff = luaL_prepbuffsize(&b, 250);
        s++;
        s = checkoption(L, s, se - s, cc + 1);
        reslen = strftime(buff, 250, cc, stm);
        ((&b)->n += (reslen));
      }
    }
    luaL_pushresult(&b);
  }
  return 1;
}
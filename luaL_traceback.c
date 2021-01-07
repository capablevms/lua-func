
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
extern void luaL_addstring(luaL_Buffer *, const char *);
extern void luaL_addvalue(luaL_Buffer *);
extern void pushfuncname(lua_State *, lua_Debug *);
extern void luaL_addvalue(luaL_Buffer *);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern int lua_getinfo(lua_State *, const char *, lua_Debug *);
extern void luaL_addvalue(luaL_Buffer *);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern int lua_getstack(lua_State *, int, lua_Debug *);
extern void luaL_addstring(luaL_Buffer *, const char *);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern void luaL_addstring(luaL_Buffer *, const char *);
extern void luaL_buffinit(lua_State *, luaL_Buffer *);
extern int lastlevel(lua_State *);

extern void luaL_traceback (lua_State *L, lua_State *L1,
                                const char *msg, int level) {
  luaL_Buffer b;
  lua_Debug ar;
  int last = lastlevel(L1);
  int limit2show = (last - level > 10 + 11) ? 10 : -1;
  luaL_buffinit(L, &b);
  if (msg) {
    luaL_addstring(&b, msg);
    ((void)((&b)->n < (&b)->size || luaL_prepbuffsize((&b), 1)), ((&b)->b[(&b)->n++] = ('\n')));
  }
  luaL_addstring(&b, "stack traceback:");
  while (lua_getstack(L1, level++, &ar)) {
    if (limit2show-- == 0) {
      int n = last - level - 11 + 1;
      lua_pushfstring(L, "\n\t...\t(skipping %d levels)", n);
      luaL_addvalue(&b);
      level += n;
    }
    else {
      lua_getinfo(L1, "Slnt", &ar);
      if (ar.currentline <= 0)
        lua_pushfstring(L, "\n\t%s: in ", ar.short_src);
      else
        lua_pushfstring(L, "\n\t%s:%d: in ", ar.short_src, ar.currentline);
      luaL_addvalue(&b);
      pushfuncname(L, &ar);
      luaL_addvalue(&b);
      if (ar.istailcall)
        luaL_addstring(&b, "\n\t(...tail calls...)");
    }
  }
  luaL_pushresult(&b);
}
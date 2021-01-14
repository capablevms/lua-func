
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

typedef struct MatchState {
  const char *src_init;
  const char *src_end;
  const char *p_end;
  lua_State *L;
  int matchdepth;
  unsigned char level;
  struct {
    const char *init;
    ptrdiff_t len;
  } capture[32];
} MatchState;


extern void lua_pushinteger(lua_State *, lua_Integer);
extern void luaL_pushresult(luaL_Buffer *);
extern void luaL_addlstring(luaL_Buffer *, const char *, size_t);
extern void lua_pushvalue(lua_State *, int);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern int add_value(MatchState *, luaL_Buffer *, const char *, const char *, int);
extern const char * match(MatchState *, const char *, const char *);
extern void reprepstate(MatchState *);
extern void prepstate(MatchState *, lua_State *, const char *, size_t, const char *, size_t);
extern void luaL_buffinit(lua_State *, luaL_Buffer *);
extern int luaL_typeerror(lua_State *, int, const char *);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern int lua_type(lua_State *, int);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

extern int str_gsub (lua_State *L) {
  size_t srcl, lp;
  const char *src = luaL_checklstring(L, 1, &srcl);
  const char *p = luaL_checklstring(L, 2, &lp);
  const char *lastmatch = ((void*)0);
  int tr = lua_type(L, 3);
  lua_Integer max_s = luaL_optinteger(L, 4, srcl + 1);
  int anchor = (*p == '^');
  lua_Integer n = 0;
  int changed = 0;
  MatchState ms;
  luaL_Buffer b;
  ((void)((tr == 3 || tr == 4 || tr == 6 || tr == 5) || luaL_typeerror(L, (3), ("string/function/table"))));


  luaL_buffinit(L, &b);
  if (anchor) {
    p++; lp--;
  }
  prepstate(&ms, L, src, srcl, p, lp);
  while (n < max_s) {
    const char *e;
    reprepstate(&ms);
    if ((e = match(&ms, src, p)) != ((void*)0) && e != lastmatch) {
      n++;
      changed = add_value(&ms, &b, src, e, tr) | changed;
      src = lastmatch = e;
    }
    else if (src < ms.src_end)
      ((void)((&b)->n < (&b)->size || luaL_prepbuffsize((&b), 1)), ((&b)->b[(&b)->n++] = (*src++)));
    else break;
    if (anchor) break;
  }
  if (!changed)
    lua_pushvalue(L, 1);
  else {
    luaL_addlstring(&b, src, ms.src_end-src);
    luaL_pushresult(&b);
  }
  lua_pushinteger(L, n);
  return 2;
}
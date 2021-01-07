
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


extern void lua_pushnil(lua_State *);
extern int push_captures(MatchState *, const char *, const char *);
extern int push_captures(MatchState *, const char *, const char *);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern const char * match(MatchState *, const char *, const char *);
extern void reprepstate(MatchState *);
extern void prepstate(MatchState *, lua_State *, const char *, size_t, const char *, size_t);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern const char * lmemfind(const char *, size_t, const char *, size_t);
extern int nospecials(const char *, size_t);
extern int lua_toboolean(lua_State *, int);
extern void lua_pushnil(lua_State *);
extern size_t posrelatI(lua_Integer, size_t);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

static int str_find_aux (lua_State *L, int find) {
  size_t ls, lp;
  const char *s = luaL_checklstring(L, 1, &ls);
  const char *p = luaL_checklstring(L, 2, &lp);
  size_t init = posrelatI(luaL_optinteger(L, 3, 1), ls) - 1;
  if (init > ls) {
    lua_pushnil(L);
    return 1;
  }

  if (find && (lua_toboolean(L, 4) || nospecials(p, lp))) {

    const char *s2 = lmemfind(s + init, ls - init, p, lp);
    if (s2) {
      lua_pushinteger(L, (s2 - s) + 1);
      lua_pushinteger(L, (s2 - s) + lp);
      return 2;
    }
  }
  else {
    MatchState ms;
    const char *s1 = s + init;
    int anchor = (*p == '^');
    if (anchor) {
      p++; lp--;
    }
    prepstate(&ms, L, s, ls, p, lp);
    do {
      const char *res;
      reprepstate(&ms);
      if ((res=match(&ms, s1, p)) != ((void*)0)) {
        if (find) {
          lua_pushinteger(L, (s1 - s) + 1);
          lua_pushinteger(L, res - s);
          return push_captures(&ms, ((void*)0), 0) + 2;
        }
        else
          return push_captures(&ms, s1, res);
      }
    } while (s1++ < ms.src_end && !anchor);
  }
  lua_pushnil(L);
  return 1;
}
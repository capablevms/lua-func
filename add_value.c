
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


extern void luaL_addvalue(luaL_Buffer *);
extern int luaL_error(lua_State *, const char *, ...);
extern const char * lua_typename(lua_State *, int);
extern int lua_type(lua_State *, int);
extern int lua_isstring(lua_State *, int);
extern void luaL_addlstring(luaL_Buffer *, const char *, size_t);
extern void lua_settop(lua_State *, int);
extern int lua_toboolean(lua_State *, int);
extern void add_s(MatchState *, luaL_Buffer *, const char *, const char *);
extern int lua_gettable(lua_State *, int);
extern void push_onecapture(MatchState *, int, const char *, const char *);
extern void lua_callk(lua_State *, int, int, lua_KContext, lua_KFunction);
extern int push_captures(MatchState *, const char *, const char *);
extern void lua_pushvalue(lua_State *, int);

static int add_value (MatchState *ms, luaL_Buffer *b, const char *s,
                                      const char *e, int tr) {
  lua_State *L = ms->L;
  switch (tr) {
    case 6: {
      int n;
      lua_pushvalue(L, 3);
      n = push_captures(ms, s, e);
      lua_callk(L, (n), (1), 0, ((void*)0));
      break;
    }
    case 5: {
      push_onecapture(ms, 0, s, e);
      lua_gettable(L, 3);
      break;
    }
    default: {
      add_s(ms, b, s, e);
      return 1;
    }
  }
  if (!lua_toboolean(L, -1)) {
    lua_settop(L, -(1)-1);
    luaL_addlstring(b, s, e - s);
    return 0;
  }
  else if (!lua_isstring(L, -1))
    return luaL_error(L, "invalid replacement value (a %s)",
                         lua_typename(L, lua_type(L,(-1))));
  else {
    luaL_addvalue(b);
    return 1;
  }
}
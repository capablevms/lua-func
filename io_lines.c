
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

typedef luaL_Stream LStream;


extern void lua_pushvalue(lua_State *, int);
extern void lua_pushnil(lua_State *);
extern void lua_pushnil(lua_State *);
extern void aux_lines(lua_State *, int);
extern void lua_settop(lua_State *, int);
extern void lua_copy(lua_State *, int, int);
extern void opencheck(lua_State *, const char *, const char *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern FILE * tofile(lua_State *);
extern void lua_settop(lua_State *, int);
extern void lua_copy(lua_State *, int, int);
extern int lua_getfield(lua_State *, int, const char *);
extern int lua_type(lua_State *, int);
extern void lua_pushnil(lua_State *);
extern int lua_type(lua_State *, int);

extern int io_lines (lua_State *L) {
  int toclose;
  if ((lua_type(L, (1)) == (-1))) lua_pushnil(L);
  if ((lua_type(L, (1)) == 0)) {
    lua_getfield(L, (-1000000 - 1000), ("_IO_" "input"));
    (lua_copy(L, -1, (1)), lua_settop(L, -(1)-1));
    tofile(L);
    toclose = 0;
  }
  else {
    const char *filename = (luaL_checklstring(L, (1), ((void*)0)));
    opencheck(L, filename, "r");
    (lua_copy(L, -1, (1)), lua_settop(L, -(1)-1));
    toclose = 1;
  }
  aux_lines(L, toclose);
  if (toclose) {
    lua_pushnil(L);
    lua_pushnil(L);
    lua_pushvalue(L, 1);
    return 4;
  }
  else
    return 1;
}
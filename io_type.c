
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


extern const char * lua_pushstring(lua_State *, const char *);
extern const char * lua_pushstring(lua_State *, const char *);
extern void lua_pushnil(lua_State *);
extern void * luaL_testudata(lua_State *, int, const char *);
extern void luaL_checkany(lua_State *, int);

static int io_type (lua_State *L) {
  LStream *p;
  luaL_checkany(L, 1);
  p = (LStream *)luaL_testudata(L, 1, "FILE*");
  if (p == ((void*)0))
    lua_pushnil(L);
  else if (((p)->closef == ((void*)0)))
    lua_pushstring(L, "" "closed file");
  else
    lua_pushstring(L, "" "file");
  return 1;
}
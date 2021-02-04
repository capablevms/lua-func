
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


extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern const char * lua_pushstring(lua_State *, const char *);
extern void * luaL_checkudata(lua_State *, int, const char *);

extern int f_tostring (lua_State *L) {
  LStream *p = ((LStream *)luaL_checkudata(L, 1, "FILE*"));
  if (((p)->closef == ((void*)0)))
    lua_pushstring(L, "" "file (closed)");
  else
    lua_pushfstring(L, "file (%p)", p->f);
  return 1;
}
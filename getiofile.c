
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


extern int luaL_error(lua_State *, const char *, ...);
extern void * lua_touserdata(lua_State *, int);
extern int lua_getfield(lua_State *, int, const char *);

static FILE *getiofile (lua_State *L, const char *findex) {
  LStream *p;
  lua_getfield(L, (-1000000 - 1000), findex);
  p = (LStream *)lua_touserdata(L, -1);
  if (((p)->closef == ((void*)0)))
    luaL_error(L, "default %s file is closed", findex + (sizeof("_IO_")/sizeof(char) - 1));
  return p->f;
}

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



extern const char * lua_tolstring(lua_State *, int, size_t *);
extern int lua_getglobal(lua_State *, const char *);

extern const char *get_prompt (lua_State *L, int firstline) {
  const char *p;
  lua_getglobal(L, firstline ? "_PROMPT" : "_PROMPT2");
  p = lua_tolstring(L, (-1), ((void*)0));
  if (p == ((void*)0)) p = (firstline ? "> " : ">> ");
  return p;
}
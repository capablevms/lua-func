
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



extern void lua_pushcclosure(lua_State *, lua_CFunction, int);
extern lua_CFunction lsys_sym(lua_State *, void *, const char *);
extern void lua_pushboolean(lua_State *, int);
extern void addtoclib(lua_State *, const char *, void *);
extern void * lsys_load(lua_State *, const char *, int);
extern void * checkclib(lua_State *, const char *);

static int lookforfunc (lua_State *L, const char *path, const char *sym) {
  void *reg = checkclib(L, path);
  if (reg == ((void*)0)) {
    reg = lsys_load(L, path, *sym == '*');
    if (reg == ((void*)0)) return 1;
    addtoclib(L, path, reg);
  }
  if (*sym == '*') {
    lua_pushboolean(L, 1);
    return 0;
  }
  else {
    lua_CFunction f = lsys_sym(L, reg, sym);
    if (f == ((void*)0))
      return 2;
    lua_pushcclosure(L, (f), 0);
    return 0;
  }
}
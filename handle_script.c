
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



extern int report(lua_State *, int);
extern int docall(lua_State *, int, int);
extern int pushargs(lua_State *);
extern int luaL_loadfilex(lua_State *, const char *, const char *);
extern int strcmp(const char *, const char *);
extern int strcmp(const char *, const char *);

static int handle_script (lua_State *L, char **argv) {
  int status;
  const char *fname = argv[0];
  if (strcmp(fname, "-") == 0 && strcmp(argv[-1], "--") != 0)
    fname = ((void*)0);
  status = luaL_loadfilex(L,fname,((void*)0));
  if (status == 0) {
    int n = pushargs(L);
    status = docall(L, n, (-1));
  }
  return report(L, status);
}
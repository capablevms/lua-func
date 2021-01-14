
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

extern const char *progname;

extern int fflush(FILE *);
extern unsigned long fwrite(const void *restrict, size_t, size_t, FILE *restrict);
extern void lua_settop(lua_State *, int);
extern int report(lua_State *, int);
extern void l_print(lua_State *);
extern int docall(lua_State *, int, int);
extern int loadline(lua_State *);

extern void doREPL (lua_State *L) {
  int status;
  const char *oldprogname = progname;
  progname = ((void*)0);
  ((void)L);
  while ((status = loadline(L)) != -1) {
    if (status == 0)
      status = docall(L, 0, (-1));
    if (status == 0) l_print(L);
    else report(L, status);
  }
  lua_settop(L, 0);
  (fwrite(("\n"), sizeof(char), (1), stdout), fflush(stdout));
  progname = oldprogname;
}
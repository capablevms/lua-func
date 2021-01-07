
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



extern int luaL_fileresult(lua_State *, int, const char *);
extern unsigned long fwrite(const void *restrict, size_t, size_t, FILE *restrict);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern int fprintf(FILE *restrict, const char *restrict, ...);
extern lua_Number lua_tonumberx(lua_State *, int, int *);
extern int fprintf(FILE *restrict, const char *restrict, ...);
extern lua_Integer lua_tointegerx(lua_State *, int, int *);
extern int lua_isinteger(lua_State *, int);
extern int lua_type(lua_State *, int);
extern int lua_gettop(lua_State *);

static int g_write (lua_State *L, FILE *f, int arg) {
  int nargs = lua_gettop(L) - arg;
  int status = 1;
  for (; nargs--; arg++) {
    if (lua_type(L, arg) == 3) {

      int len = lua_isinteger(L, arg)
                ? fprintf(f, "%" "ll" "d",
                             (long long)lua_tointegerx(L,(arg),((void*)0)))
                : fprintf(f, "%.14g",
                             (double)lua_tonumberx(L,(arg),((void*)0)));
      status = status && (len > 0);
    }
    else {
      size_t l;
      const char *s = luaL_checklstring(L, arg, &l);
      status = status && (fwrite(s, sizeof(char), l, f) == l);
    }
  }
  if (status) return 1;
  else return luaL_fileresult(L, status, ((void*)0));
}
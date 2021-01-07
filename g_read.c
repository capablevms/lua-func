
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

typedef struct {
  FILE *f;
  int c;
  int n;
  char buff[200 + 1];
} RN;


extern void lua_pushnil(lua_State *);
extern void lua_settop(lua_State *, int);
extern int luaL_fileresult(lua_State *, int, const char *);
extern int ferror(FILE *);
extern int luaL_argerror(lua_State *, int, const char *);
extern void read_all(lua_State *, FILE *);
extern int read_line(lua_State *, FILE *, int);
extern int read_line(lua_State *, FILE *, int);
extern int read_number(lua_State *, FILE *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern int read_chars(lua_State *, FILE *, size_t);
extern int test_eof(lua_State *, FILE *);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern int lua_type(lua_State *, int);
extern void luaL_checkstack(lua_State *, int, const char *);
extern int read_line(lua_State *, FILE *, int);
extern void clearerr(FILE *);
extern int lua_gettop(lua_State *);

static int g_read (lua_State *L, FILE *f, int first) {
  int nargs = lua_gettop(L) - 1;
  int n, success;
  clearerr(f);
  if (nargs == 0) {
    success = read_line(L, f, 1);
    n = first + 1;
  }
  else {

    luaL_checkstack(L, nargs+20, "too many arguments");
    success = 1;
    for (n = first; nargs-- && success; n++) {
      if (lua_type(L, n) == 3) {
        size_t l = (size_t)luaL_checkinteger(L, n);
        success = (l == 0) ? test_eof(L, f) : read_chars(L, f, l);
      }
      else {
        const char *p = (luaL_checklstring(L, (n), ((void*)0)));
        if (*p == '*') p++;
        switch (*p) {
          case 'n':
            success = read_number(L, f);
            break;
          case 'l':
            success = read_line(L, f, 1);
            break;
          case 'L':
            success = read_line(L, f, 0);
            break;
          case 'a':
            read_all(L, f);
            success = 1;
            break;
          default:
            return luaL_argerror(L, n, "invalid format");
        }
      }
    }
  }
  if (ferror(f))
    return luaL_fileresult(L, 0, ((void*)0));
  if (!success) {
    lua_settop(L, -(1)-1);
    lua_pushnil(L);
  }
  return n - first;
}
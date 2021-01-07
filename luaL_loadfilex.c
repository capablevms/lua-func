
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

typedef struct LoadF {
  int n;
  FILE *f;
  char buff[8192];
} LoadF;


extern void lua_settop(lua_State *, int);
extern void lua_rotate(lua_State *, int, int);
extern int errfile(lua_State *, const char *, int);
extern void lua_settop(lua_State *, int);
extern int fclose(FILE *);
extern int ferror(FILE *);
extern int lua_load(lua_State *, lua_Reader, void *, const char *, const char *);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern int skipcomment(LoadF *, int *);
extern int errfile(lua_State *, const char *, int);
extern FILE * freopen(const char *restrict, const char *restrict, FILE *restrict);
extern int skipcomment(LoadF *, int *);
extern int errfile(lua_State *, const char *, int);
extern FILE * fopen(const char *restrict, const char *restrict);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern const char * lua_pushstring(lua_State *, const char *);
extern int lua_gettop(lua_State *);

extern int luaL_loadfilex (lua_State *L, const char *filename,
                                             const char *mode) {
  LoadF lf;
  int status, readstatus;
  int c;
  int fnameindex = lua_gettop(L) + 1;
  if (filename == ((void*)0)) {
    lua_pushstring(L, "" "=stdin");
    lf.f = stdin;
  }
  else {
    lua_pushfstring(L, "@%s", filename);
    lf.f = fopen(filename, "r");
    if (lf.f == ((void*)0)) return errfile(L, "open", fnameindex);
  }
  if (skipcomment(&lf, &c))
    lf.buff[lf.n++] = '\n';
  if (c == "\x1bLua"[0] && filename) {
    lf.f = freopen(filename, "rb", lf.f);
    if (lf.f == ((void*)0)) return errfile(L, "reopen", fnameindex);
    skipcomment(&lf, &c);
  }
  if (c != (-1))
    lf.buff[lf.n++] = c;
  status = lua_load(L, getF, &lf, lua_tolstring(L, (-1), ((void*)0)), mode);
  readstatus = ferror(lf.f);
  if (filename) fclose(lf.f);
  if (readstatus) {
    lua_settop(L, fnameindex);
    return errfile(L, "read", fnameindex);
  }
  (lua_rotate(L, (fnameindex), -1), lua_settop(L, -(1)-1));
  return status;
}

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



extern const char * lua_pushlstring(lua_State *, const char *, size_t);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern unsigned long strlen(const char *);
extern void lua_settop(lua_State *, int);
extern char * fgets(char *restrict, int, FILE *restrict);
extern int fflush(FILE *);
extern int fputs(const char *restrict, FILE *restrict);
extern const char * get_prompt(lua_State *, int);

extern int pushline (lua_State *L, int firstline) {
  char buffer[512];
  char *b = buffer;
  size_t l;
  const char *prmt = get_prompt(L, firstline);
  int readstatus = ((void)L, fputs(prmt, stdout), fflush(stdout), fgets(b, 512, stdin) != ((void*)0));
  if (readstatus == 0)
    return 0;
  lua_settop(L, -(1)-1);
  l = strlen(b);
  if (l > 0 && b[l-1] == '\n')
    b[--l] = '\0';
  if (firstline && b[0] == '=')
    lua_pushfstring(L, "return %s", b + 1);
  else
    lua_pushlstring(L, b, l);
  { (void)L; (void)b; };
  return 1;
}
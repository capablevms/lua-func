
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



extern void lua_settop(lua_State *, int);
extern int fflush(FILE *);
extern int fprintf(FILE *restrict, const char *restrict, ...);
extern const char * luaL_tolstring(lua_State *, int, size_t *);
extern int lua_pcallk(lua_State *, int, int, int, lua_KContext, lua_KFunction);
extern int luaL_loadbufferx(lua_State *, const char *, size_t, const char *, const char *);
extern unsigned long strlen(const char *);
extern int strcmp(const char *, const char *);
extern char * fgets(char *restrict, int, FILE *restrict);
extern int fflush(FILE *);
extern int fprintf(FILE *restrict, const char *restrict, ...);

extern int db_debug (lua_State *L) {
  for (;;) {
    char buffer[250];
    (fprintf(stderr, ("%s"), ("lua_debug> ")), fflush(stderr));
    if (fgets(buffer, sizeof(buffer), stdin) == 0 ||
        strcmp(buffer, "cont\n") == 0)
      return 0;
    if (luaL_loadbufferx(L,buffer,strlen(buffer),"=(debug command)",((void*)0)) ||
        lua_pcallk(L, (0), (0), (0), 0, ((void*)0)))
      (fprintf(stderr, ("%s\n"), (luaL_tolstring(L, -1, ((void*)0)))), fflush(stderr));
    lua_settop(L, 0);
  }
}
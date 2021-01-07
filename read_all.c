
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



extern void luaL_pushresult(luaL_Buffer *);
extern unsigned long fread(void *restrict, size_t, size_t, FILE *restrict);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern void luaL_buffinit(lua_State *, luaL_Buffer *);

static void read_all (lua_State *L, FILE *f) {
  size_t nr;
  luaL_Buffer b;
  luaL_buffinit(L, &b);
  do {
    char *p = luaL_prepbuffsize(&b, ((int)(16 * sizeof(void*) * sizeof(lua_Number))));
    nr = fread(p, sizeof(char), ((int)(16 * sizeof(void*) * sizeof(lua_Number))), f);
    ((&b)->n += (nr));
  } while (nr == ((int)(16 * sizeof(void*) * sizeof(lua_Number))));
  luaL_pushresult(&b);
}
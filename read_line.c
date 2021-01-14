
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



extern lua_Unsigned lua_rawlen(lua_State *, int);
extern void luaL_pushresult(luaL_Buffer *);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern int getc(FILE *);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern void luaL_buffinit(lua_State *, luaL_Buffer *);

extern int read_line (lua_State *L, FILE *f, int chop) {
  luaL_Buffer b;
  int c;
  luaL_buffinit(L, &b);
  do {
    char *buff = luaL_prepbuffsize(&b, ((int)(16 * sizeof(void*) * sizeof(lua_Number))));
    int i = 0;
    ((void)0);
    while (i < ((int)(16 * sizeof(void*) * sizeof(lua_Number))) && (c = getc(f)) != (-1) && c != '\n')
      buff[i++] = c;
    ((void)0);
    ((&b)->n += (i));
  } while (c != (-1) && c != '\n');
  if (!chop && c == '\n')
    ((void)((&b)->n < (&b)->size || luaL_prepbuffsize((&b), 1)), ((&b)->b[(&b)->n++] = (c)));
  luaL_pushresult(&b);

  return (c == '\n' || lua_rawlen(L, -1) > 0);
}
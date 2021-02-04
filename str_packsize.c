
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

typedef enum KOption {
  Kint,
  Kuint,
  Kfloat,
  Kchar,
  Kstring,
  Kzstr,
  Kpadding,
  Kpaddalign,
  Knop
} KOption;
typedef struct Header {
  lua_State *L;
  int islittle;
  int maxalign;
} Header;


extern void lua_pushinteger(lua_State *, lua_Integer);
extern int luaL_argerror(lua_State *, int, const char *);
extern int luaL_argerror(lua_State *, int, const char *);
extern KOption getdetails(Header *, size_t, const char **, int *, int *);
extern void initheader(lua_State *, Header *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

extern int str_packsize (lua_State *L) {
  Header h;
  const char *fmt = (luaL_checklstring(L, (1), ((void*)0)));
  size_t totalsize = 0;
  initheader(L, &h);
  while (*fmt != '\0') {
    int size, ntoalign;
    KOption opt = getdetails(&h, totalsize, &fmt, &size, &ntoalign);
    ((void)((opt != Kstring && opt != Kzstr) || luaL_argerror(L, (1), ("variable-length format"))));

    size += ntoalign;
    ((void)((totalsize <= (sizeof(size_t) < sizeof(int) ? ((size_t)(~(size_t)0)) : (size_t)(2147483647)) - size) || luaL_argerror(L, (1), ("format result too large"))));

    totalsize += size;
  }
  lua_pushinteger(L, (lua_Integer)totalsize);
  return 1;
}
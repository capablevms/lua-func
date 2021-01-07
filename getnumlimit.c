
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

typedef struct Header {
  lua_State *L;
  int islittle;
  int maxalign;
} Header;


extern int luaL_error(lua_State *, const char *, ...);
extern int getnum(const char **, int);

static int getnumlimit (Header *h, const char **fmt, int df) {
  int sz = getnum(fmt, df);
  if (sz > 16 || sz <= 0)
    return luaL_error(h->L, "integral size (%d) out of limits [1,%d]",
                            sz, 16);
  return sz;
}
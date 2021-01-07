
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



extern const TValue * luaH_getint(Table *, lua_Integer);
extern const TValue * luaH_getint(Table *, lua_Integer);
extern const TValue * luaH_getint(Table *, lua_Integer);

static lua_Unsigned hash_search (Table *t, lua_Unsigned j) {
  lua_Unsigned i;
  if (j == 0) j++;
  do {
    i = j;
    if (j <= ((lua_Unsigned)(9223372036854775807LL)) / 2)
      j *= 2;
    else {
      j = 9223372036854775807LL;
      if ((((((((luaH_getint(t, j)))->tt_)) & 0x0F)) == (0)))
        break;
      else
        return j;
    }
  } while (!(((((((luaH_getint(t, j)))->tt_)) & 0x0F)) == (0)));

  while (j - i > 1u) {
    lua_Unsigned m = (i + j) / 2;
    if ((((((((luaH_getint(t, m)))->tt_)) & 0x0F)) == (0))) j = m;
    else i = m;
  }
  return i;
}

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



extern int luaL_error(lua_State *, const char *, ...);

extern lua_Integer unpackint (lua_State *L, const char *str,
                              int islittle, int size, int issigned) {
  lua_Unsigned res = 0;
  int i;
  int limit = (size <= ((int)sizeof(lua_Integer))) ? size : ((int)sizeof(lua_Integer));
  for (i = limit - 1; i >= 0; i--) {
    res <<= 8;
    res |= (lua_Unsigned)(unsigned char)str[islittle ? i : size - 1 - i];
  }
  if (size < ((int)sizeof(lua_Integer))) {
    if (issigned) {
      lua_Unsigned mask = (lua_Unsigned)1 << (size*8 - 1);
      res = ((res ^ mask) - mask);
    }
  }
  else if (size > ((int)sizeof(lua_Integer))) {
    int mask = (!issigned || (lua_Integer)res >= 0) ? 0 : ((1 << 8) - 1);
    for (i = limit; i < size; i++) {
      if ((unsigned char)str[islittle ? i : size - 1 - i] != mask)
        luaL_error(L, "%d-byte integer does not fit into Lua Integer", size);
    }
  }
  return (lua_Integer)res;
}

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



extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);

extern void packint (luaL_Buffer *b, lua_Unsigned n,
                     int islittle, int size, int neg) {
  char *buff = luaL_prepbuffsize(b, size);
  int i;
  buff[islittle ? 0 : size - 1] = (char)(n & ((1 << 8) - 1));
  for (i = 1; i < size; i++) {
    n >>= 8;
    buff[islittle ? i : size - 1 - i] = (char)(n & ((1 << 8) - 1));
  }
  if (neg && size > ((int)sizeof(lua_Integer))) {
    for (i = ((int)sizeof(lua_Integer)); i < size; i++)
      buff[islittle ? i : size - 1 - i] = (char)((1 << 8) - 1);
  }
  ((b)->n += (size));
}
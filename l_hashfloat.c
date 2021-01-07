
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



extern double frexp(double, int *);

static int l_hashfloat (lua_Number n) {
  int i;
  lua_Integer ni;
  n = frexp(n, &i) * -((lua_Number)(((-2147483647 -1))));
  if (!((n) >= (double)((-9223372036854775807LL -1LL)) && (n) < -(double)((-9223372036854775807LL -1LL)) && (*(&ni) = (long long)(n), 1))) {
    ((void)0);
    return 0;
  }
  else {
    unsigned int u = ((unsigned int)((i))) + ((unsigned int)((ni)));
    return ((int)((u <= ((unsigned int)((2147483647))) ? u : ~u)));
  }
}

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



extern int digit(int);
extern int digit(int);

static int getnum (const char **fmt, int df) {
  if (!digit(**fmt))
    return df;
  else {
    int a = 0;
    do {
      a = a*10 + (*((*fmt)++) - '0');
    } while (digit(**fmt) && a <= ((int)(sizeof(size_t) < sizeof(int) ? ((size_t)(~(size_t)0)) : (size_t)(2147483647)) - 9)/10);
    return a;
  }
}
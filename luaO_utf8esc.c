
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




int luaO_utf8esc (char *buff, unsigned long x) {
  int n = 1;
  ((void)0);
  if (x < 0x80)
    buff[8 - 1] = ((char)((x)));
  else {
    unsigned int mfb = 0x3f;
    do {
      buff[8 - (n++)] = ((char)((0x80 | (x & 0x3f))));
      x >>= 6;
      mfb >>= 1;
    } while (x > mfb);
    buff[8 - n] = ((char)(((~mfb << 1) | x)));
  }
  return n;
}

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

typedef unsigned int utfint;



extern const char *utf8_decode (const char *s, utfint *val, int strict) {
  static const utfint limits[] =
        {~(utfint)0, 0x80, 0x800, 0x10000u, 0x200000u, 0x4000000u};
  unsigned int c = (unsigned char)s[0];
  utfint res = 0;
  if (c < 0x80)
    res = c;
  else {
    int count = 0;
    for (; c & 0x40; c <<= 1) {
      unsigned int cc = (unsigned char)s[++count];
      if ((cc & 0xC0) != 0x80)
        return ((void*)0);
      res = (res << 6) | (cc & 0x3F);
    }
    res |= ((utfint)(c & 0x7F) << (count * 5));
    if (count > 5 || res > 0x7FFFFFFFu || res < limits[count])
      return ((void*)0);
    s += count;
  }
  if (strict) {

    if (res > 0x10FFFFu || (0xD800u <= res && res <= 0xDFFFu))
      return ((void*)0);
  }
  if (val) *val = res;
  return s + 1;
}

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



extern unsigned long strlen(const char *);
extern char * strpbrk(const char *, const char *);

extern int nospecials (const char *p, size_t l) {
  size_t upto = 0;
  do {
    if (strpbrk(p + upto, "^$*+?.([%-"))
      return 0;
    upto += strlen(p + upto) + 1;
  } while (upto <= l);
  return 1;
}

#include <time.h>
#include <setjmp.h>
#include <ctype.h>
#include <locale.h>

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



extern struct lconv * localeconv();
extern unsigned long strspn(const char *, const char *);
extern int snprintf(char *restrict, size_t, const char *restrict, ...);
extern int snprintf(char *restrict, size_t, const char *restrict, ...);

extern int tostringbuff (TValue *obj, char *buff) {
  int len;
  ((void)0);
  if (((((obj))->tt_) == (((3) | ((0) << 4)))))
    len = snprintf((buff),44,"%" "ll" "d",(long long)((((obj)->value_).i)));
  else {
    len = snprintf((buff),44,"%.14g",(double)((((obj)->value_).n)));
    if (buff[strspn(buff, "-0123456789")] == '\0') {
      buff[len++] = (localeconv()->decimal_point[0]);
      buff[len++] = '0';
    }
  }
  return len;
}
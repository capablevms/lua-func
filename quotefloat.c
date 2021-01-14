
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



extern int snprintf(char *restrict, size_t, const char *restrict, ...);
extern void * memchr(const void *, int, size_t);

extern int quotefloat (lua_State *L, char *buff, lua_Number n) {
  const char *s;
  if (n == (lua_Number)(__builtin_huge_val ()))
    s = "1e9999";
  else if (n == -(lua_Number)(__builtin_huge_val ()))
    s = "-1e9999";
  else if (n != n)
    s = "(0/0)";
  else {
    int nb = ((void)L, snprintf(buff,120,"%" "" "a",(double)(n)));


    if (memchr(buff, '.', nb) == ((void*)0)) {
      char point = (localeconv()->decimal_point[0]);
      char *ppoint = (char *)memchr(buff, point, nb);
      if (ppoint) *ppoint = '.';
    }
    return nb;
  }

  return snprintf(buff,120,"%s",s);
}
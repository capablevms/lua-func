
#include <time.h>
#include <setjmp.h>
#include <locale.h>
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



extern const char * l_str2dloc(const char *, lua_Number *, int);
extern struct lconv * localeconv();
extern char * strcpy(char *restrict, const char *restrict);
extern unsigned long strlen(const char *);
extern char * strchr(const char *, int);
extern const char * l_str2dloc(const char *, lua_Number *, int);
extern char * strpbrk(const char *, const char *);

extern const char *l_str2d (const char *s, lua_Number *result) {
  const char *endptr;
  const char *pmode = strpbrk(s, ".xXnN");
  int mode = pmode ? ((((unsigned char)((*pmode)))) | ('A' ^ 'a')) : 0;
  if (mode == 'n')
    return ((void*)0);
  endptr = l_str2dloc(s, result, mode);
  if (endptr == ((void*)0)) {
    char buff[200 + 1];
    const char *pdot = strchr(s, '.');
    if (strlen(s) > 200 || pdot == ((void*)0))
      return ((void*)0);
    strcpy(buff, s);
    buff[pdot - s] = (localeconv()->decimal_point[0]);
    endptr = l_str2dloc(buff, result, mode);
    if (endptr != ((void*)0))
      endptr = s + (endptr - buff);
  }
  return endptr;
}
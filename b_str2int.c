
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



extern unsigned long strspn(const char *, const char *);
extern const unsigned short ** __ctype_b_loc();
extern int toupper(int);
extern const unsigned short ** __ctype_b_loc();
extern const unsigned short ** __ctype_b_loc();
extern unsigned long strspn(const char *, const char *);

static const char *b_str2int (const char *s, int base, lua_Integer *pn) {
  lua_Unsigned n = 0;
  int neg = 0;
  s += strspn(s, " \f\n\r\t\v");
  if (*s == '-') { s++; neg = 1; }
  else if (*s == '+') s++;
  if (!((*__ctype_b_loc ())[(int) (((unsigned char)*s))] & (unsigned short int) _ISalnum))
    return ((void*)0);
  do {
    int digit = (((*__ctype_b_loc ())[(int) (((unsigned char)*s))] & (unsigned short int) _ISdigit)) ? *s - '0'
                   : (toupper((unsigned char)*s) - 'A') + 10;
    if (digit >= base) return ((void*)0);
    n = n * base + digit;
    s++;
  } while (((*__ctype_b_loc ())[(int) (((unsigned char)*s))] & (unsigned short int) _ISalnum));
  s += strspn(s, " \f\n\r\t\v");
  *pn = (lua_Integer)((neg) ? (0u - n) : n);
  return s;
}
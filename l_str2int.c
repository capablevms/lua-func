
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



extern int luaO_hexavalue(int);
extern int isneg(const char **);

extern const char *l_str2int (const char *s, lua_Integer *result) {
  lua_Unsigned a = 0;
  int empty = 1;
  int neg;
  while ((luai_ctype_[(((unsigned char)((*s))))+1] & ((1 << (3))))) s++;
  neg = isneg(&s);
  if (s[0] == '0' &&
      (s[1] == 'x' || s[1] == 'X')) {
    s += 2;
    for (; (luai_ctype_[(((unsigned char)((*s))))+1] & ((1 << (4)))); s++) {
      a = a * 16 + luaO_hexavalue(*s);
      empty = 0;
    }
  }
  else {
    for (; (luai_ctype_[(((unsigned char)((*s))))+1] & ((1 << (1)))); s++) {
      int d = *s - '0';
      if (a >= ((lua_Unsigned)(9223372036854775807LL / 10)) && (a > ((lua_Unsigned)(9223372036854775807LL / 10)) || d > ((int)((9223372036854775807LL % 10))) + neg))
        return ((void*)0);
      a = a * 10 + d;
      empty = 0;
    }
  }
  while ((luai_ctype_[(((unsigned char)((*s))))+1] & ((1 << (3))))) s++;
  if (empty || *s != '\0') return ((void*)0);
  else {
    *result = ((lua_Integer)((neg) ? 0u - a : a));
    return s;
  }
}
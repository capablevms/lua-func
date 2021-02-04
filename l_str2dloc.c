
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



extern double strtod(const char *restrict, char **restrict);
extern double strtod(const char *restrict, char **restrict);

extern const char *l_str2dloc (const char *s, lua_Number *result, int mode) {
  char *endptr;
  *result = (mode == 'x') ? strtod((s), (&endptr))
                          : strtod((s), (&endptr));
  if (endptr == s) return ((void*)0);
  while ((luai_ctype_[(((unsigned char)((*endptr))))+1] & ((1 << (3))))) endptr++;
  return (*endptr == '\0') ? endptr : ((void*)0);
}
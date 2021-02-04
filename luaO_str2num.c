
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



extern const char * l_str2d(const char *, lua_Number *);
extern const char * l_str2int(const char *, lua_Integer *);

size_t luaO_str2num (const char *s, TValue *o) {
  lua_Integer i; lua_Number n;
  const char *e;
  if ((e = l_str2int(s, &i)) != ((void*)0)) {
    { TValue *io=(o); ((io)->value_).i=(i); ((io)->tt_=(((3) | ((0) << 4)))); };
  }
  else if ((e = l_str2d(s, &n)) != ((void*)0)) {
    { TValue *io=(o); ((io)->value_).n=(n); ((io)->tt_=(((3) | ((1) << 4)))); };
  }
  else
    return 0;
  return (e - s) + 1;
}

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



extern int addk(FuncState *, TValue *, TValue *);

static int luaK_intK (FuncState *fs, lua_Integer n) {
  TValue k, o;
  { TValue *io=(&k); ((io)->value_).p=(((void *)((((size_t)((n))))))); ((io)->tt_=(((2) | ((0) << 4)))); };
  { TValue *io=(&o); ((io)->value_).i=(n); ((io)->tt_=(((3) | ((0) << 4)))); };
  return addk(fs, &k, &o);
}
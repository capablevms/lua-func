
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

typedef struct BuffFS {
  lua_State *L;
  int pushed;
  int blen;
  char space[200];
} BuffFS;


extern void __builtin_va_end(struct __va_list_tag *);
extern const char * luaO_pushvfstring(lua_State *, const char *, struct __va_list_tag *);
extern void __builtin_va_start(struct __va_list_tag *, ...);

const char *luaO_pushfstring (lua_State *L, const char *fmt, ...) {
  const char *msg;
  va_list argp;
  __builtin_va_start(argp, fmt);
  msg = luaO_pushvfstring(L, fmt, argp);
  __builtin_va_end(argp);
  return msg;
}
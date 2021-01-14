
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

typedef struct {
  lua_State *L;
  ZIO *Z;
  const char *name;
} LoadState;


extern void error(LoadState *, const char *);
extern int memcmp(const void *, const void *, size_t);
extern void loadBlock(LoadState *, void *, size_t);
extern unsigned long strlen(const char *);

extern void checkliteral (LoadState *S, const char *s, const char *msg) {
  char buff[sizeof("\x1bLua") + sizeof("\x19\x93\r\n\x1a\n")];
  size_t len = strlen(s);
  loadBlock(S,buff,(len)*sizeof((buff)[0]));
  if (memcmp(s, buff, len) != 0)
    error(S, msg);
}
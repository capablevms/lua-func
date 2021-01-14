
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
extern int luaZ_fill(ZIO *);

extern lu_byte loadByte (LoadState *S) {
  int b = (((S->Z)->n--)>0 ? ((unsigned char)((*(S->Z)->p++))) : luaZ_fill(S->Z));
  if (b == (-1))
    error(S, "truncated chunk");
  return ((lu_byte)((b)));
}
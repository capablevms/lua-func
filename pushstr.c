
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


extern void luaV_concat(lua_State *, int);
extern TString * luaS_newlstr(lua_State *, const char *, size_t);

static void pushstr (BuffFS *buff, const char *str, size_t l) {
  lua_State *L = buff->L;
  { TValue *io = ((&(L->top)->val)); TString *x_ = (luaS_newlstr(L, str, l)); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((x_->tt) | (1 << 6)))); ((void)L, ((void)0)); };
  L->top++;
  buff->pushed++;
  luaV_concat(L, buff->pushed);
  buff->pushed = 1;
}
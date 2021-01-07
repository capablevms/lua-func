
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



extern int luaO_rawarith(lua_State *, int, const TValue *, const TValue *, TValue *);
extern int validop(int, TValue *, TValue *);
extern int tonumeral(const expdesc *, TValue *);
extern int tonumeral(const expdesc *, TValue *);

static int constfolding (FuncState *fs, int op, expdesc *e1,
                                        const expdesc *e2) {
  TValue v1, v2, res;
  if (!tonumeral(e1, &v1) || !tonumeral(e2, &v2) || !validop(op, &v1, &v2))
    return 0;
  luaO_rawarith(fs->ls->L, op, &v1, &v2, &res);
  if (((((&res))->tt_) == (((3) | ((0) << 4))))) {
    e1->k = VKINT;
    e1->u.ival = (((&res)->value_).i);
  }
  else {
    lua_Number n = (((&res)->value_).n);
    if ((!(((n))==((n)))) || n == 0)
      return 0;
    e1->k = VKFLT;
    e1->u.nval = n;
  }
  return 1;
}
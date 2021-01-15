
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

extern int l_strcmp (const TString *, const TString *);

extern int lessthanothers (lua_State *L, const TValue *l, const TValue *r) {
  ((void)0);
  if ((((((((l))->tt_)) & 0x0F)) == (4)) && (((((((r))->tt_)) & 0x0F)) == (4)))
    return l_strcmp(((&((((union GCUnion *)((((l)->value_).gc))))->ts))), ((&((((union GCUnion *)((((r)->value_).gc))))->ts)))) < 0;
  else
    return luaT_callorderTM(L, l, r, TM_LT);
}

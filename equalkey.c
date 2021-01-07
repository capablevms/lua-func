
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



extern int luaS_eqlngstr(TString *, TString *);

static int equalkey (const TValue *k1, const Node *n2, int deadok) {
  if ((((k1)->tt_) != ((n2)->u.key_tt)) &&
       !(deadok && (((n2)->u.key_tt) == (9 +2)) && (((k1)->tt_) & (1 << 6))))
   return 0;
  switch (((n2)->u.key_tt)) {
    case ((0) | ((0) << 4)): case ((1) | ((0) << 4)): case ((1) | ((1) << 4)):
      return 1;
    case ((3) | ((0) << 4)):
      return ((((k1)->value_).i) == (((n2)->u.key_val).i));
    case ((3) | ((1) << 4)):
      return (((((k1)->value_).n))==(((((n2)->u.key_val)).n)));
    case ((2) | ((0) << 4)):
      return (((k1)->value_).p) == ((((n2)->u.key_val)).p);
    case ((6) | ((1) << 4)):
      return (((k1)->value_).f) == ((((n2)->u.key_val)).f);
    case ((((4) | ((1) << 4))) | (1 << 6)):
      return luaS_eqlngstr(((&((((union GCUnion *)((((k1)->value_).gc))))->ts))), ((&((((union GCUnion *)((((n2)->u.key_val).gc))))->ts))));
    default:
      return (((k1)->value_).gc) == ((((n2)->u.key_val)).gc);
  }
}
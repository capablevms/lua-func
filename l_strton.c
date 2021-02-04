
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

extern int l_strton (const TValue *obj, TValue *result) {
  ((void)0);
  if (!(((((((obj))->tt_)) & 0x0F)) == (4)))
    return 0;
  else
    return (luaO_str2num(((((&((((union GCUnion *)((((obj)->value_).gc))))->ts))))->contents), result) == ((((&((((union GCUnion *)((((obj)->value_).gc))))->ts))))->tt == ((4) | ((0) << 4)) ? (((&((((union GCUnion *)((((obj)->value_).gc))))->ts))))->shrlen : (((&((((union GCUnion *)((((obj)->value_).gc))))->ts))))->u.lnglen) + 1);
}



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




static void *touserdata (const TValue *o) {
  switch ((((((o)->tt_)) & 0x0F))) {
    case 7: return (((char *)((((&((((union GCUnion *)((((o)->value_).gc))))->u)))))) + (((((&((((union GCUnion *)((((o)->value_).gc))))->u))))->nuvalue) == 0 ? __builtin_offsetof(Udata0, bindata) : __builtin_offsetof(Udata, uv) + (sizeof(UValue) * ((((&((((union GCUnion *)((((o)->value_).gc))))->u))))->nuvalue))));
    case 2: return (((o)->value_).p);
    default: return ((void*)0);
  }
}
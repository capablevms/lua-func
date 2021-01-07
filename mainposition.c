
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



extern unsigned int luaS_hashlongstr(TString *);
extern int l_hashfloat(lua_Number);

static Node *mainposition (const Table *t, int ktt, const Value *kvl) {
  switch (((ktt) & 0x3F)) {
    case ((3) | ((0) << 4)):
      return ((&(t)->node[(((((int)((((((*kvl).i))) & ((((1<<((t)->lsizenode))))-1)))))))]));
    case ((3) | ((1) << 4)):
      return ((&(t)->node[((l_hashfloat(((*kvl).n))) % ((((1<<((t)->lsizenode)))-1)|1))]));
    case ((4) | ((0) << 4)):
      return ((&(t)->node[(((((int)(((((((&((((union GCUnion *)(((*kvl).gc))))->ts))))->hash)) & ((((1<<((t)->lsizenode))))-1)))))))]));
    case ((4) | ((1) << 4)):
      return ((&(t)->node[(((((int)((((luaS_hashlongstr(((&((((union GCUnion *)(((*kvl).gc))))->ts)))))) & ((((1<<((t)->lsizenode))))-1)))))))]));
    case ((1) | ((0) << 4)):
      return ((&(t)->node[(((((int)((((0)) & ((((1<<((t)->lsizenode))))-1)))))))]));
    case ((1) | ((1) << 4)):
      return ((&(t)->node[(((((int)((((1)) & ((((1<<((t)->lsizenode))))-1)))))))]));
    case ((2) | ((0) << 4)):
      return ((&(t)->node[((((unsigned int)((size_t)(((*kvl).p)) & (2147483647 *2U +1U)))) % ((((1<<((t)->lsizenode)))-1)|1))]));
    case ((6) | ((1) << 4)):
      return ((&(t)->node[((((unsigned int)((size_t)(((*kvl).f)) & (2147483647 *2U +1U)))) % ((((1<<((t)->lsizenode)))-1)|1))]));
    default:
      return ((&(t)->node[((((unsigned int)((size_t)(((*kvl).gc)) & (2147483647 *2U +1U)))) % ((((1<<((t)->lsizenode)))-1)|1))]));
  }
}
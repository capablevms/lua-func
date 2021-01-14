
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



extern int countint(lua_Integer, unsigned int *);

extern int numusehash (const Table *t, unsigned int *nums, unsigned int *pna) {
  int totaluse = 0;
  int ause = 0;
  int i = ((1<<((t)->lsizenode)));
  while (i--) {
    Node *n = &t->node[i];
    if (!((((((((&(n)->i_val)))->tt_)) & 0x0F)) == (0))) {
      if ((((n)->u.key_tt) == ((3) | ((0) << 4))))
        ause += countint((((n)->u.key_val).i), nums);
      totaluse++;
    }
  }
  *pna += ause;
  return totaluse;
}

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




extern unsigned int numusearray (const Table *t, unsigned int *nums) {
  int lg;
  unsigned int ttlg;
  unsigned int ause = 0;
  unsigned int i = 1;
  unsigned int asize = (t->alimit);

  for (lg = 0, ttlg = 1; lg <= ((int)((sizeof(int) * 8 - 1))); lg++, ttlg *= 2) {
    unsigned int lc = 0;
    unsigned int lim = ttlg;
    if (lim > asize) {
      lim = asize;
      if (i > lim)
        break;
    }

    for (; i <= lim; i++) {
      if (!(((((((&t->array[i-1]))->tt_)) & 0x0F)) == (0)))
        lc++;
    }
    nums[lg] += lc;
    ause += lc;
  }
  return ause;
}
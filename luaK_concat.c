
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



extern void fixjump(FuncState *, int, int);
extern int getjump(FuncState *, int);

void luaK_concat (FuncState *fs, int *l1, int l2) {
  if (l2 == (-1)) return;
  else if (*l1 == (-1))
    *l1 = l2;
  else {
    int list = *l1;
    int next;
    while ((next = getjump(fs, list)) != (-1))
      list = next;
    fixjump(fs, list, l2);
  }
}

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



extern void luaE_setdebt(global_State *, l_mem);

extern void setpause (global_State *g) {
  l_mem threshold, debt;
  int pause = ((g->gcpause) * 4);
  l_mem estimate = g->GCestimate / 100;
  ((void)0);
  threshold = (pause < ((l_mem)(((lu_mem)(~(lu_mem)0)) >> 1)) / estimate)
            ? estimate * pause
            : ((l_mem)(((lu_mem)(~(lu_mem)0)) >> 1));
  debt = ((lu_mem)((g)->totalbytes + (g)->GCdebt)) - threshold;
  if (debt > 0) debt = 0;
  luaE_setdebt(g, debt);
}
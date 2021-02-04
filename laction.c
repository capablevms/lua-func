
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

extern lua_State *globalL;
extern void lstop (lua_State *L, lua_Debug *ar);

extern void lua_sethook(lua_State *, lua_Hook, int, int);
extern __sighandler_t signal(int, __sighandler_t);

extern void laction (int i) {
  int flag = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
  signal(i, ((__sighandler_t) 0));
  lua_sethook(globalL, lstop, flag, 1);
}
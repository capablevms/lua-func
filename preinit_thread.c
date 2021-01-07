
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




static void preinit_thread (lua_State *L, global_State *g) {
  (L->l_G) = g;
  L->stack = ((void*)0);
  L->ci = ((void*)0);
  L->nci = 0;
  L->twups = L;
  L->errorJmp = ((void*)0);
  L->hook = ((void*)0);
  L->hookmask = 0;
  L->basehookcount = 0;
  L->allowhook = 1;
  (L->hookcount = L->basehookcount);
  L->openupval = ((void*)0);
  L->status = 0;
  L->errfunc = 0;
  L->oldpc = 0;
}
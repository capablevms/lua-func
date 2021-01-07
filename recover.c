
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



extern void luaD_shrinkstack(lua_State *);
extern void luaD_seterrorobj(lua_State *, int, StkId);
extern int luaF_close(lua_State *, StkId, int);
extern CallInfo * findpcall(lua_State *);

static int recover (lua_State *L, int status) {
  StkId oldtop;
  CallInfo *ci = findpcall(L);
  if (ci == ((void*)0)) return 0;

  oldtop = ((StkId)((char *)L->stack + (ci->u2.funcidx)));
  L->ci = ci;
  L->allowhook = ((ci->callstatus) & (1<<0));
  status = luaF_close(L, oldtop, status);
  oldtop = ((StkId)((char *)L->stack + (ci->u2.funcidx)));
  luaD_seterrorobj(L, status, oldtop);
  luaD_shrinkstack(L);
  L->errfunc = ci->u.c.old_errfunc;
  return 1;
}
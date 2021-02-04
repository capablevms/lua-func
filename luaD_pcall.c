
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
extern long __builtin_expect(long, long);
extern int luaD_rawrunprotected(lua_State *, Pfunc, void *);

int luaD_pcall (lua_State *L, Pfunc func, void *u,
                ptrdiff_t old_top, ptrdiff_t ef) {
  int status;
  CallInfo *old_ci = L->ci;
  lu_byte old_allowhooks = L->allowhook;
  ptrdiff_t old_errfunc = L->errfunc;
  L->errfunc = ef;
  status = luaD_rawrunprotected(L, func, u);
  if ((__builtin_expect(((status != 0) != 0), 0))) {
    StkId oldtop = ((StkId)((char *)L->stack + (old_top)));
    L->ci = old_ci;
    L->allowhook = old_allowhooks;
    status = luaF_close(L, oldtop, status);
    oldtop = ((StkId)((char *)L->stack + (old_top)));
    luaD_seterrorobj(L, status, oldtop);
    luaD_shrinkstack(L);
  }
  L->errfunc = old_errfunc;
  return status;
}
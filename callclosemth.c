
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



extern void luaE_warnerror(lua_State *, const char *);
extern int luaD_pcall(lua_State *, Pfunc, void *, ptrdiff_t, ptrdiff_t);
extern int prepclosingmethod(lua_State *, TValue *, TValue *);
extern void luaD_seterrorobj(lua_State *, int, StkId);
extern void varerror(lua_State *, StkId, const char *);
extern void callclose(lua_State *, void *);
extern int prepclosingmethod(lua_State *, TValue *, TValue *);
extern long __builtin_expect(long, long);

extern int callclosemth (lua_State *L, StkId level, int status) {
  TValue *uv = (&(level)->val);
  if ((__builtin_expect(((status == 0) != 0), 1))) {
    if (prepclosingmethod(L, uv, &(L->l_G)->nilvalue))
      callclose(L, ((void*)0));
    else if (!(((((uv))->tt_) == (((1) | ((0) << 4)))) || (((((((uv))->tt_)) & 0x0F)) == (0))))
      varerror(L, level, "attempt to close non-closable variable '%s'");
  }
  else {
    ptrdiff_t oldtop;
    level++;
    oldtop = ((char *)(level + 1) - (char *)L->stack);
    luaD_seterrorobj(L, status, level);
    if (prepclosingmethod(L, uv, (&(level)->val))) {
      int newstatus = luaD_pcall(L, callclose, ((void*)0), oldtop, 0);
      if (newstatus != 0 && status == (-2))
        status = newstatus;
      else {
        if (newstatus != 0)
          luaE_warnerror(L, "__close metamethod");

        L->top = ((StkId)((char *)L->stack + (oldtop)));
      }
    }

  }
  return status;
}
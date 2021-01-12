
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



extern void luaD_throw(lua_State *, int);
extern void callclose(lua_State *, void *);
extern int prepclosingmethod(lua_State *, TValue *, TValue *);
extern void luaD_seterrorobj(lua_State *, int, StkId);
extern long __builtin_expect(long, long);
extern int luaD_rawrunprotected(lua_State *, Pfunc, void *);
extern void varerror(lua_State *, StkId, const char *);
extern const TValue * luaT_gettmbyobj(lua_State *, const TValue *, TMS);

static void trynewtbcupval (lua_State *, void *);

void luaF_newtbcupval (lua_State *L, StkId level) {
  TValue *obj = (&(level)->val);
  ((void)0);
  if (!(((((obj))->tt_) == (((1) | ((0) << 4)))) || (((((((obj))->tt_)) & 0x0F)) == (0)))) {
    int status;
    const TValue *tm = luaT_gettmbyobj(L, obj, TM_CLOSE);
    if ((((((((tm))->tt_)) & 0x0F)) == (0)))
      varerror(L, level, "variable '%s' got a non-closable value");
    status = luaD_rawrunprotected(L, trynewtbcupval, level);
    if ((__builtin_expect(((status != 0) != 0), 0))) {
      ((void)0);
      luaD_seterrorobj(L, 4, level + 1);

      prepclosingmethod(L, (&(level)->val), (&(level + 1)->val));
      callclose(L, ((void*)0));
      luaD_throw(L, 4);
    }
  }
}
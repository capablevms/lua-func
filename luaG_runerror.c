
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



extern void luaG_errormsg(lua_State *);
extern const char * luaG_addinfo(lua_State *, const char *, TString *, int);
extern int getcurrentline(CallInfo *);
extern const char * luaO_pushvfstring(lua_State *, const char *, va_list);
extern void luaC_step(lua_State *);

void __attribute__((noreturn)) luaG_runerror (lua_State *L, const char *fmt, ...) {
  CallInfo *ci = L->ci;
  const char *msg;
  va_list argp;
  { if ((L->l_G)->GCdebt > 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); };
  __builtin_va_start(argp, fmt);
  msg = luaO_pushvfstring(L, fmt, argp);
  __builtin_va_end(argp);
  if ((!((ci)->callstatus & (1<<1))))
    luaG_addinfo(L, msg, (((&((((union GCUnion *)(((((&((ci)->func)->val))->value_).gc))))->cl.l))))->p->source, getcurrentline(ci));
  luaG_errormsg(L);
}
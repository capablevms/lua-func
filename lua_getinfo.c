
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



extern void collectvalidlines(lua_State *, Closure *);
extern char * strchr(const char *, int);
extern char * strchr(const char *, int);
extern int auxgetinfo(lua_State *, const char *, lua_Debug *, Closure *, CallInfo *);

extern int lua_getinfo (lua_State *L, const char *what, lua_Debug *ar) {
  int status;
  Closure *cl;
  CallInfo *ci;
  TValue *func;
  ((void) 0);
  if (*what == '>') {
    ci = ((void*)0);
    func = (&(L->top - 1)->val);
    ((void)L, ((void)0));
    what++;
    L->top--;
  }
  else {
    ci = ar->i_ci;
    func = (&(ci->func)->val);
    ((void)0);
  }
  cl = ((((func)->tt_) & 0x1F) == ((6) | ((0) << 4))) ? ((&((((union GCUnion *)((((func)->value_).gc))))->cl))) : ((void*)0);
  status = auxgetinfo(L, what, ar, cl, ci);
  if (strchr(what, 'f')) {
    { TValue *io1=((&(L->top)->val)); const TValue *io2=(func); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
    {L->top++; ((void)L, ((void)0));};
  }
  if (strchr(what, 'L'))
    collectvalidlines(L, cl);
  ((void) 0);
  return status;
}
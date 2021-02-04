
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



extern int luaF_close(lua_State *, StkId, int);

extern void moveresults (lua_State *L, StkId res, int nres, int wanted) {
  StkId firstresult;
  int i;
  switch (wanted) {
    case 0:
      L->top = res;
      return;
    case 1:
      if (nres == 0)
        (((&(res)->val))->tt_=(((0) | ((0) << 4))));
      else
        { TValue *io1=((&(res)->val)); const TValue *io2=((&(L->top - nres)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
      L->top = res + 1;
      return;
    case (-1):
      wanted = nres;
      break;
    default:
      if (((wanted) < (-1))) {
        ptrdiff_t savedres = ((char *)(res) - (char *)L->stack);
        luaF_close(L, res, 0);
        res = ((StkId)((char *)L->stack + (savedres)));
        wanted = (-(wanted) - 3);
        if (wanted == (-1))
          wanted = nres;
      }
      break;
  }
  firstresult = L->top - nres;

  for (i = 0; i < nres && i < wanted; i++)
    { TValue *io1=((&(res + i)->val)); const TValue *io2=((&(firstresult + i)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
  for (; i < wanted; i++)
    (((&(res + i)->val))->tt_=(((0) | ((0) << 4))));
  L->top = res + wanted;
}
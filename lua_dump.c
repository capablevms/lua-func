
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



extern int luaU_dump(lua_State *, const Proto *, lua_Writer, void *, int);

extern int lua_dump (lua_State *L, lua_Writer writer, void *data, int strip) {
  int status;
  TValue *o;
  ((void) 0);
  ((void)L, ((void)0));
  o = (&(L->top - 1)->val);
  if (((((o))->tt_) == (((((6) | ((0) << 4))) | (1 << 6)))))
    status = luaU_dump(L, (((&((((union GCUnion *)((((o)->value_).gc))))->cl.l)))->p), writer, data, strip);
  else
    status = 1;
  ((void) 0);
  return status;
}
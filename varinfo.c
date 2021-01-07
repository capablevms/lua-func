
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



extern const char * luaO_pushfstring(lua_State *, const char *, ...);
extern const char * getobjname(const Proto *, int, int, const char **);
extern int currentpc(CallInfo *);
extern int isinstack(CallInfo *, const TValue *);
extern const char * getupvalname(CallInfo *, const TValue *, const char **);

static const char *varinfo (lua_State *L, const TValue *o) {
  const char *name = ((void*)0);
  CallInfo *ci = L->ci;
  const char *kind = ((void*)0);
  if ((!((ci)->callstatus & (1<<1)))) {
    kind = getupvalname(ci, o, &name);
    if (!kind && isinstack(ci, o))
      kind = getobjname((((&((((union GCUnion *)(((((&((ci)->func)->val))->value_).gc))))->cl.l))))->p, currentpc(ci),
                        ((int)((((StkId)(o)) - (ci->func + 1)))), &name);
  }
  return (kind) ? luaO_pushfstring(L, " (%s '%s')", kind, name) : "";
}
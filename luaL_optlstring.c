
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



extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern unsigned long strlen(const char *);
extern int lua_type(lua_State *, int);

extern const char *luaL_optlstring (lua_State *L, int arg,
                                        const char *def, size_t *len) {
  if ((lua_type(L, (arg)) <= 0)) {
    if (len)
      *len = (def ? strlen(def) : 0);
    return def;
  }
  else return luaL_checklstring(L, arg, len);
}
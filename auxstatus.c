
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



extern int lua_gettop(lua_State *);
extern int lua_getstack(lua_State *, int, lua_Debug *);
extern int lua_status(lua_State *);

static int auxstatus (lua_State *L, lua_State *co) {
  if (L == co) return 0;
  else {
    switch (lua_status(co)) {
      case 1:
        return 2;
      case 0: {
        lua_Debug ar;
        if (lua_getstack(co, 0, &ar))
          return 3;
        else if (lua_gettop(co) == 0)
            return 1;
        else
          return 2;
      }
      default:
        return 1;
    }
  }
}
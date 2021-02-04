
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



extern int stringK(FuncState *, TString *);
extern int luaK_numberK(FuncState *, lua_Number);
extern int luaK_intK(FuncState *, lua_Integer);
extern int nilK(FuncState *);
extern int boolF(FuncState *);
extern int boolT(FuncState *);

extern int luaK_exp2K (FuncState *fs, expdesc *e) {
  if (!((e)->t != (e)->f)) {
    int info;
    switch (e->k) {
      case VTRUE: info = boolT(fs); break;
      case VFALSE: info = boolF(fs); break;
      case VNIL: info = nilK(fs); break;
      case VKINT: info = luaK_intK(fs, e->u.ival); break;
      case VKFLT: info = luaK_numberK(fs, e->u.nval); break;
      case VKSTR: info = stringK(fs, e->u.strval); break;
      case VK: info = e->u.info; break;
      default: return 0;
    }
    if (info <= ((1<<8)-1)) {
      e->k = VK;
      e->u.info = info;
      return 1;
    }
  }

  return 0;
}
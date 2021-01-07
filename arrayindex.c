
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




static unsigned int arrayindex (lua_Integer k) {
  if (((lua_Unsigned)(k)) - 1u < ((((size_t)((1u << ((int)((sizeof(int) * 8 - 1)))))) <= ((size_t)(~(size_t)0))/sizeof(TValue)) ? (1u << ((int)((sizeof(int) * 8 - 1)))) : ((unsigned int)(((((size_t)(~(size_t)0))/sizeof(TValue)))))))
    return ((unsigned int)((k)));
  else
    return 0;
}
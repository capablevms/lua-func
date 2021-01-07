
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



extern void luaM_free_(lua_State *, void *, size_t);

void luaE_shrinkCI (lua_State *L) {
  CallInfo *ci = L->ci->next;
  CallInfo *next;
  if (ci == ((void*)0))
    return;
  while ((next = ci->next) != ((void*)0)) {
    CallInfo *next2 = next->next;
    ci->next = next2;
    L->nci--;
    luaM_free_(L, (next), sizeof(*(next)));
    if (next2 == ((void*)0))
      break;
    else {
      next2->previous = ci;
      ci = next2;
    }
  }
}
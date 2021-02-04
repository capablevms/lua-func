
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



extern void * memcpy(void *restrict, const void *restrict, size_t);
extern TString * luaS_createlngstrobj(lua_State *, size_t);
extern void luaM_toobig(lua_State *);
extern long __builtin_expect(long, long);
extern TString * internshrstr(lua_State *, const char *, size_t);

TString *luaS_newlstr (lua_State *L, const char *str, size_t l) {
  if (l <= 40)
    return internshrstr(L, str, l);
  else {
    TString *ts;
    if ((__builtin_expect(((l >= ((sizeof(size_t) < sizeof(lua_Integer) ? ((size_t)(~(size_t)0)) : (size_t)(9223372036854775807LL)) - sizeof(TString))/sizeof(char)) != 0), 0)))
      luaM_toobig(L);
    ts = luaS_createlngstrobj(L, l);
    memcpy(((ts)->contents), str, l * sizeof(char));
    return ts;
  }
}
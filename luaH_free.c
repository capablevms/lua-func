
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
extern void luaM_free_(lua_State *, void *, size_t);
extern unsigned int luaH_realasize(const Table *);
extern void freehash(lua_State *, Table *);

void luaH_free (lua_State *L, Table *t) {
  freehash(L, t);
  luaM_free_(L, (t->array), (luaH_realasize(t))*sizeof(*(t->array)));
  luaM_free_(L, (t), sizeof(*(t)));
}
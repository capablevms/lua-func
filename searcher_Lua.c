
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



extern int checkload(lua_State *, int, const char *);
extern int luaL_loadfilex(lua_State *, const char *, const char *);
extern const char * findfile(lua_State *, const char *, const char *, const char *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

static int searcher_Lua (lua_State *L) {
  const char *filename;
  const char *name = (luaL_checklstring(L, (1), ((void*)0)));
  filename = findfile(L, name, "path", "/");
  if (filename == ((void*)0)) return 1;
  return checkload(L, (luaL_loadfilex(L,filename,((void*)0)) == 0), filename);
}
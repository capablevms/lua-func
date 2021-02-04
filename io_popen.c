
#include <time.h>
#include <setjmp.h>
#include <ctype.h>
#include <stdio.h>

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

typedef luaL_Stream LStream;


extern int luaL_fileresult(lua_State *, int, const char *);
extern int luaL_error(lua_State *, const char *, ...);
extern int luaL_argerror(lua_State *, int, const char *);
extern LStream * newprefile(lua_State *);
extern const char * luaL_optlstring(lua_State *, int, const char *, size_t *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

extern int io_pclose (lua_State *);

#define l_checkmodep(m)	((m[0] == 'r' || m[0] == 'w') && m[1] == '\0')
#define l_popen(L,c,m)		(fflush(NULL), popen(c,m))
#define l_pclose(L,file)	(pclose(file))

extern int io_popen (lua_State *L) {
  const char *filename = luaL_checkstring(L, 1);
  const char *mode = luaL_optstring(L, 2, "r");
  LStream *p = newprefile(L);
  luaL_argcheck(L, l_checkmodep(mode), 2, "invalid mode");
  p->f = l_popen(L, filename, mode);
  p->closef = &io_pclose;
  return (p->f == NULL) ? luaL_fileresult(L, 0, filename) : 1;
}

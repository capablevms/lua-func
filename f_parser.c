
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



extern void luaF_initupvals(lua_State *, LClosure *);
extern LClosure * luaY_parser(lua_State *, ZIO *, Mbuffer *, Dyndata *, const char *, int);
extern void checkmode(lua_State *, const char *, const char *);
extern LClosure * luaU_undump(lua_State *, ZIO *, const char *);
extern void checkmode(lua_State *, const char *, const char *);
extern int luaZ_fill(ZIO *);

static void f_parser (lua_State *L, void *ud) {
  LClosure *cl;
  struct SParser *p = ((struct SParser *)(ud));
  int c = (((p->z)->n--)>0 ? ((unsigned char)((*(p->z)->p++))) : luaZ_fill(p->z));
  if (c == "\x1bLua"[0]) {
    checkmode(L, p->mode, "binary");
    cl = luaU_undump(L, p->z, p->name);
  }
  else {
    checkmode(L, p->mode, "text");
    cl = luaY_parser(L, p->z, &p->buff, &p->dyd, p->name, c);
  }
  ((void)0);
  luaF_initupvals(L, cl);
}
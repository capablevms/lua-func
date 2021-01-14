
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

struct SParser {  /* data to 'f_parser' */
  ZIO *z;
  Mbuffer buff;  /* dynamic structure used by the scanner */
  Dyndata dyd;  /* dynamic structures used by the parser */
  const char *mode;
  const char *name;
};

extern void luaM_free_(lua_State *, void *, size_t);
extern void luaM_free_(lua_State *, void *, size_t);
extern void luaM_free_(lua_State *, void *, size_t);
extern void * luaM_saferealloc_(lua_State *, void *, size_t, size_t);
extern int luaD_pcall(lua_State *, Pfunc, void *, ptrdiff_t, ptrdiff_t);

extern void f_parser (lua_State *, void *);

int luaD_protectedparser (lua_State *L, ZIO *z, const char *name,
                                        const char *mode) {
  struct SParser p;
  int status;
  ((L)->nCcalls += 0x10000);
  p.z = z; p.name = name; p.mode = mode;
  p.dyd.actvar.arr = ((void*)0); p.dyd.actvar.size = 0;
  p.dyd.gt.arr = ((void*)0); p.dyd.gt.size = 0;
  p.dyd.label.arr = ((void*)0); p.dyd.label.size = 0;
  ((&p.buff)->buffer = ((void*)0), (&p.buff)->buffsize = 0);
  status = luaD_pcall(L, f_parser, &p, ((char *)(L->top) - (char *)L->stack), L->errfunc);
  ((&p.buff)->buffer = ((char *)((luaM_saferealloc_(L, ((&p.buff)->buffer), ((&p.buff)->buffsize)*sizeof(char), (0)*sizeof(char))))), (&p.buff)->buffsize = 0);
  luaM_free_(L, (p.dyd.actvar.arr), (p.dyd.actvar.size)*sizeof(*(p.dyd.actvar.arr)));
  luaM_free_(L, (p.dyd.gt.arr), (p.dyd.gt.size)*sizeof(*(p.dyd.gt.arr)));
  luaM_free_(L, (p.dyd.label.arr), (p.dyd.label.size)*sizeof(*(p.dyd.label.arr)));
  ((L)->nCcalls -= 0x10000);
  return status;
}
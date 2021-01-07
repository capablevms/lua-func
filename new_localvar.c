
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



extern void * luaM_growaux_(lua_State *, void *, int, int *, int, int, const char *);
extern void checklimit(FuncState *, int, int, const char *);

static int new_localvar (LexState *ls, TString *name) {
  lua_State *L = ls->L;
  FuncState *fs = ls->fs;
  Dyndata *dyd = ls->dyd;
  Vardesc *var;
  checklimit(fs, dyd->actvar.n + 1 - fs->firstlocal,
                 200, "local variables");
  ((dyd->actvar.arr)=((Vardesc *)(luaM_growaux_(L,dyd->actvar.arr,dyd->actvar.n + 1,&(dyd->actvar.size),sizeof(Vardesc), ((((size_t)(((32767 *2 +1)))) <= ((size_t)(~(size_t)0))/sizeof(Vardesc)) ? ((32767 *2 +1)) : ((unsigned int)(((((size_t)(~(size_t)0))/sizeof(Vardesc)))))),"local variables"))));

  var = &dyd->actvar.arr[dyd->actvar.n++];
  var->vd.kind = 0;
  var->vd.name = name;
  return dyd->actvar.n - 1 - fs->firstlocal;
}
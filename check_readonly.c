
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



extern void luaK_semerror(LexState *, const char *);
extern const char * luaO_pushfstring(lua_State *, const char *, ...);
extern Vardesc * getlocalvardesc(FuncState *, int);

static void check_readonly (LexState *ls, expdesc *e) {
  FuncState *fs = ls->fs;
  TString *varname = ((void*)0);
  switch (e->k) {
    case VCONST: {
      varname = ls->dyd->actvar.arr[e->u.info].vd.name;
      break;
    }
    case VLOCAL: {
      Vardesc *vardesc = getlocalvardesc(fs, e->u.var.vidx);
      if (vardesc->vd.kind != 0)
        varname = vardesc->vd.name;
      break;
    }
    case VUPVAL: {
      Upvaldesc *up = &fs->f->upvalues[e->u.info];
      if (up->kind != 0)
        varname = up->name;
      break;
    }
    default:
      return;
  }
  if (varname) {
    const char *msg = luaO_pushfstring(ls->L,
       "attempt to assign to const variable '%s'", ((varname)->contents));
    luaK_semerror(ls, msg);
  }
}
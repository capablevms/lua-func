
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



extern void setminordebt(global_State *);
extern void youngcollection(lua_State *, global_State *);
extern void setpause(global_State *);
extern void setminordebt(global_State *);
extern lu_mem fullgen(lua_State *, global_State *);
extern void stepgenfull(lua_State *, global_State *);

static void genstep (lua_State *L, global_State *g) {
  if (g->lastatomic != 0)
    stepgenfull(L, g);
  else {
    lu_mem majorbase = g->GCestimate;
    lu_mem majorinc = (majorbase / 100) * ((g->genmajormul) * 4);
    if (g->GCdebt > 0 && ((lu_mem)((g)->totalbytes + (g)->GCdebt)) > majorbase + majorinc) {
      lu_mem numobjs = fullgen(L, g);
      if (((lu_mem)((g)->totalbytes + (g)->GCdebt)) < majorbase + (majorinc / 2)) {


        setminordebt(g);
      }
      else {
        g->lastatomic = numobjs;
        setpause(g);
      }
    }
    else {
      youngcollection(L, g);
      setminordebt(g);
      g->GCestimate = majorbase;
    }
  }
  ((void)0);
}

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



extern void luaD_shrinkstack(lua_State *);
extern void reallymarkobject(global_State *, GCObject *);
extern void reallymarkobject(global_State *, GCObject *);
extern void linkgclist_(GCObject *, GCObject **, GCObject **);

static int traversethread (global_State *g, lua_State *th) {
  UpVal *uv;
  StkId o = th->stack;
  if ((((th)->marked & 7) > 1) || g->gcstate == 0)
    linkgclist_((&(((union GCUnion *)((th)))->gc)), &(th)->gclist, &(g->grayagain));
  if (o == ((void*)0))
    return 1;
  ((void)0);

  for (; o < th->top; o++)
    { ((void)g->mainthread, ((void)0)); if ((((((&(o)->val))->tt_) & (1 << 6)) && (((((((&(o)->val))->value_).gc))->marked) & (((1<<(3)) | (1<<(4))))))) reallymarkobject(g,((((&(o)->val))->value_).gc)); };
  for (uv = th->openupval; uv != ((void*)0); uv = uv->u.open.next)
    { if ((((uv)->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g, (&(((union GCUnion *)((uv)))->gc))); };
  if (g->gcstate == 2) {
    for (; o < th->stack_last; o++)
      (((&(o)->val))->tt_=(((0) | ((0) << 4))));

    if (!(th->twups != th) && th->openupval != ((void*)0)) {
      th->twups = g->twups;
      g->twups = th;
    }
  }
  else if (!g->gcemergency)
    luaD_shrinkstack(th);
  return 1 + ((int)(((th)->stack_last - (th)->stack)));
}
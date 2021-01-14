
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



extern void genlink(global_State *, GCObject *);
extern void reallymarkobject(global_State *, GCObject *);
extern void reallymarkobject(global_State *, GCObject *);

extern int traverseudata (global_State *g, Udata *u) {
  int i;
  { if (u->metatable) { if ((((u->metatable)->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g, (&(((union GCUnion *)((u->metatable)))->gc))); }; };
  for (i = 0; i < u->nuvalue; i++)
    { ((void)g->mainthread, ((void)0)); if (((((&u->uv[i].uv)->tt_) & (1 << 6)) && ((((((&u->uv[i].uv)->value_).gc))->marked) & (((1<<(3)) | (1<<(4))))))) reallymarkobject(g,(((&u->uv[i].uv)->value_).gc)); };
  genlink(g, (&(((union GCUnion *)((u)))->gc)));
  return 1 + u->nuvalue;
}
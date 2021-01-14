
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



extern void reallymarkobject(global_State *, GCObject *);
extern void reallymarkobject(global_State *, GCObject *);
extern void reallymarkobject(global_State *, GCObject *);
extern void reallymarkobject(global_State *, GCObject *);
extern void reallymarkobject(global_State *, GCObject *);

extern int traverseproto (global_State *g, Proto *f) {
  int i;
  { if (f->source) { if ((((f->source)->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g, (&(((union GCUnion *)((f->source)))->gc))); }; };
  for (i = 0; i < f->sizek; i++)
    { ((void)g->mainthread, ((void)0)); if (((((&f->k[i])->tt_) & (1 << 6)) && ((((((&f->k[i])->value_).gc))->marked) & (((1<<(3)) | (1<<(4))))))) reallymarkobject(g,(((&f->k[i])->value_).gc)); };
  for (i = 0; i < f->sizeupvalues; i++)
    { if (f->upvalues[i].name) { if ((((f->upvalues[i].name)->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g, (&(((union GCUnion *)((f->upvalues[i].name)))->gc))); }; };
  for (i = 0; i < f->sizep; i++)
    { if (f->p[i]) { if ((((f->p[i])->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g, (&(((union GCUnion *)((f->p[i])))->gc))); }; };
  for (i = 0; i < f->sizelocvars; i++)
    { if (f->locvars[i].varname) { if ((((f->locvars[i].varname)->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g, (&(((union GCUnion *)((f->locvars[i].varname)))->gc))); }; };
  return 1 + f->sizek + f->sizeupvalues + f->sizep + f->sizelocvars;
}
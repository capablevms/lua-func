
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



extern void traversestrongtable(global_State *, Table *);
extern void linkgclist_(GCObject *, GCObject **, GCObject **);
extern int traverseephemeron(global_State *, Table *, int);
extern void traverseweakvalue(global_State *, Table *);
extern char * strchr(const char *, int);
extern char * strchr(const char *, int);
extern void reallymarkobject(global_State *, GCObject *);
extern const TValue * luaT_gettm(Table *, TMS, TString *);

static lu_mem traversetable (global_State *g, Table *h) {
  const char *weakkey, *weakvalue;
  const TValue *mode = ((h->metatable) == ((void*)0) ? ((void*)0) : ((h->metatable)->flags & (1u<<(TM_MODE))) ? ((void*)0) : luaT_gettm(h->metatable, TM_MODE, (g)->tmname[TM_MODE]));
  { if (h->metatable) { if ((((h->metatable)->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g, (&(((union GCUnion *)((h->metatable)))->gc))); }; };
  if (mode && (((((((mode))->tt_)) & 0x0F)) == (4)) &&
      (((void)((weakkey = strchr(((((&((((union GCUnion *)((((mode)->value_).gc))))->ts))))->contents), 'k')))),
       ((void)((weakvalue = strchr(((((&((((union GCUnion *)((((mode)->value_).gc))))->ts))))->contents), 'v')))),
       (weakkey || weakvalue))) {
    if (!weakkey)
      traverseweakvalue(g, h);
    else if (!weakvalue)
      traverseephemeron(g, h, 0);
    else
      linkgclist_((&(((union GCUnion *)((h)))->gc)), &(h)->gclist, &(g->allweak));
  }
  else
    traversestrongtable(g, h);
  return 1 + h->alimit + 2 * (((h)->lastfree == ((void*)0)) ? 0 : ((1<<((h)->lsizenode))));
}
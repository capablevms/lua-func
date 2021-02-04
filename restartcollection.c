
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



extern lu_mem markbeingfnz(global_State *);
extern void markmt(global_State *);
extern void reallymarkobject(global_State *, GCObject *);
extern void reallymarkobject(global_State *, GCObject *);
extern void cleargraylists(global_State *);

extern void restartcollection (global_State *g) {
  cleargraylists(g);
  { if ((((g->mainthread)->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g, (&(((union GCUnion *)((g->mainthread)))->gc))); };
  { ((void)g->mainthread, ((void)0)); if (((((&g->l_registry)->tt_) & (1 << 6)) && ((((((&g->l_registry)->value_).gc))->marked) & (((1<<(3)) | (1<<(4))))))) reallymarkobject(g,(((&g->l_registry)->value_).gc)); };
  markmt(g);
  markbeingfnz(g);
}
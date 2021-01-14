
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

extern int iscleared (global_State *g, const GCObject *o) {
  if (o == ((void*)0)) return 0;
  else if (((o->tt) & 0x0F) == 4) {
    { if ((((o)->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g, (&(((union GCUnion *)((o)))->gc))); };
    return 0;
  }
  else return (((o)->marked) & (((1<<(3)) | (1<<(4)))));
}
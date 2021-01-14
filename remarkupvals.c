
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

extern int remarkupvals (global_State *g) {
  lua_State *thread;
  lua_State **p = &g->twups;
  int work = 0;
  while ((thread = *p) != ((void*)0)) {
    work++;
    if (!(((thread)->marked) & (((1<<(3)) | (1<<(4))))) && thread->openupval != ((void*)0))
      p = &thread->twups;
    else {
      UpVal *uv;
      ((void)0);
      *p = thread->twups;
      thread->twups = thread;
      for (uv = thread->openupval; uv != ((void*)0); uv = uv->u.open.next) {
        ((void)0);
        work++;
        if (!(((uv)->marked) & (((1<<(3)) | (1<<(4)))))) {
          ((void)0);
          { ((void)g->mainthread, ((void)0)); if (((((uv->v)->tt_) & (1 << 6)) && ((((((uv->v)->value_).gc))->marked) & (((1<<(3)) | (1<<(4))))))) reallymarkobject(g,(((uv->v)->value_).gc)); };
        }
      }
    }
  }
  return work;
}
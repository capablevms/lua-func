
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



extern void __builtin_va_end(struct __va_list_tag *);
extern void luaC_changemode(lua_State *, int);
extern void luaC_changemode(lua_State *, int);
extern void luaC_step(lua_State *);
extern void luaE_setdebt(global_State *, l_mem);
extern void luaC_step(lua_State *);
extern void luaE_setdebt(global_State *, l_mem);
extern void luaC_fullgc(lua_State *, int);
extern void luaE_setdebt(global_State *, l_mem);
extern void __builtin_va_start(struct __va_list_tag *, ...);

extern int lua_gc (lua_State *L, int what, ...) {
  va_list argp;
  int res = 0;
  global_State *g;
  ((void) 0);
  g = (L->l_G);
  __builtin_va_start(argp, what);
  switch (what) {
    case 0: {
      g->gcrunning = 0;
      break;
    }
    case 1: {
      luaE_setdebt(g, 0);
      g->gcrunning = 1;
      break;
    }
    case 2: {
      luaC_fullgc(L, 0);
      break;
    }
    case 3: {

      res = ((int)((((lu_mem)((g)->totalbytes + (g)->GCdebt)) >> 10)));
      break;
    }
    case 4: {
      res = ((int)((((lu_mem)((g)->totalbytes + (g)->GCdebt)) & 0x3ff)));
      break;
    }
    case 5: {
      int data = __builtin_va_arg(argp, int);
      l_mem debt = 1;
      lu_byte oldrunning = g->gcrunning;
      g->gcrunning = 1;
      if (data == 0) {
        luaE_setdebt(g, 0);
        luaC_step(L);
      }
      else {
        debt = ((l_mem)(data)) * 1024 + g->GCdebt;
        luaE_setdebt(g, debt);
        { if ((L->l_G)->GCdebt > 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); };
      }
      g->gcrunning = oldrunning;
      if (debt > 0 && g->gcstate == 8)
        res = 1;
      break;
    }
    case 6: {
      int data = __builtin_va_arg(argp, int);
      res = ((g->gcpause) * 4);
      ((g->gcpause) = (data) / 4);
      break;
    }
    case 7: {
      int data = __builtin_va_arg(argp, int);
      res = ((g->gcstepmul) * 4);
      ((g->gcstepmul) = (data) / 4);
      break;
    }
    case 9: {
      res = g->gcrunning;
      break;
    }
    case 10: {
      int minormul = __builtin_va_arg(argp, int);
      int majormul = __builtin_va_arg(argp, int);
      res = (g->gckind == 1 || g->lastatomic != 0) ? 10 : 11;
      if (minormul != 0)
        g->genminormul = minormul;
      if (majormul != 0)
        ((g->genmajormul) = (majormul) / 4);
      luaC_changemode(L, 1);
      break;
    }
    case 11: {
      int pause = __builtin_va_arg(argp, int);
      int stepmul = __builtin_va_arg(argp, int);
      int stepsize = __builtin_va_arg(argp, int);
      res = (g->gckind == 1 || g->lastatomic != 0) ? 10 : 11;
      if (pause != 0)
        ((g->gcpause) = (pause) / 4);
      if (stepmul != 0)
        ((g->gcstepmul) = (stepmul) / 4);
      if (stepsize != 0)
        g->gcstepsize = stepsize;
      luaC_changemode(L, 0);
      break;
    }
    default: res = -1;
  }
  __builtin_va_end(argp);
  ((void) 0);
  return res;
}
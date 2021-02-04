
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



extern void luaM_free_(lua_State *, void *, size_t);
extern void luaM_free_(lua_State *, void *, size_t);
extern void luaS_remove(lua_State *, TString *);
extern void luaM_free_(lua_State *, void *, size_t);
extern void luaE_freethread(lua_State *, lua_State *);
extern void luaH_free(lua_State *, Table *);
extern void luaM_free_(lua_State *, void *, size_t);
extern void luaM_free_(lua_State *, void *, size_t);
extern void freeupval(lua_State *, UpVal *);
extern void luaF_freeproto(lua_State *, Proto *);

extern void freeobj (lua_State *L, GCObject *o) {
  switch (o->tt) {
    case (((9 +1)) | ((0) << 4)):
      luaF_freeproto(L, (&((((union GCUnion *)((o))))->p)));
      break;
    case ((9) | ((0) << 4)):
      freeupval(L, (&((((union GCUnion *)((o))))->upv)));
      break;
    case ((6) | ((0) << 4)): {
      LClosure *cl = (&((((union GCUnion *)((o))))->cl.l));
      luaM_free_(L, (cl), ((((int)((__builtin_offsetof(LClosure, upvals)))) + ((int)((sizeof(TValue *)))) * (cl->nupvalues))));
      break;
    }
    case ((6) | ((2) << 4)): {
      CClosure *cl = (&((((union GCUnion *)((o))))->cl.c));
      luaM_free_(L, (cl), ((((int)((__builtin_offsetof(CClosure, upvalue)))) + ((int)((sizeof(TValue)))) * (cl->nupvalues))));
      break;
    }
    case ((5) | ((0) << 4)):
      luaH_free(L, (&((((union GCUnion *)((o))))->h)));
      break;
    case ((8) | ((0) << 4)):
      luaE_freethread(L, (&((((union GCUnion *)((o))))->th)));
      break;
    case ((7) | ((0) << 4)): {
      Udata *u = (&((((union GCUnion *)((o))))->u));
      luaM_free_(L, (o), ((((u->nuvalue) == 0 ? __builtin_offsetof(Udata0, bindata) : __builtin_offsetof(Udata, uv) + (sizeof(UValue) * (u->nuvalue))) + (u->len))));
      break;
    }
    case ((4) | ((0) << 4)): {
      TString *ts = (&((((union GCUnion *)((o))))->ts));
      luaS_remove(L, ts);
      luaM_free_(L, (ts), ((__builtin_offsetof(TString, contents) + ((ts->shrlen) + 1) * sizeof(char))));
      break;
    }
    case ((4) | ((1) << 4)): {
      TString *ts = (&((((union GCUnion *)((o))))->ts));
      luaM_free_(L, (ts), ((__builtin_offsetof(TString, contents) + ((ts->u.lnglen) + 1) * sizeof(char))));
      break;
    }
    default: ((void)0);
  }
}
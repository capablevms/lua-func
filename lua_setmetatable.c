
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



extern void luaC_checkfinalizer(lua_State *, GCObject *, Table *);
extern void luaC_barrier_(lua_State *, GCObject *, GCObject *);
extern void luaC_checkfinalizer(lua_State *, GCObject *, Table *);
extern void luaC_barrier_(lua_State *, GCObject *, GCObject *);
extern TValue * index2value(lua_State *, int);

extern int lua_setmetatable (lua_State *L, int objindex) {
  TValue *obj;
  Table *mt;
  ((void) 0);
  ((void)L, ((void)0));
  obj = index2value(L, objindex);
  if (((((((((&(L->top - 1)->val)))->tt_)) & 0x0F)) == (0)))
    mt = ((void*)0);
  else {
    ((void)L, ((void)0));
    mt = ((&((((union GCUnion *)(((((&(L->top - 1)->val))->value_).gc))))->h)));
  }
  switch ((((((obj)->tt_)) & 0x0F))) {
    case 5: {
      ((&((((union GCUnion *)((((obj)->value_).gc))))->h)))->metatable = mt;
      if (mt) {
        ( (((((((obj)->value_).gc))->marked) & ((1<<(5)))) && (((mt)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(&(((union GCUnion *)(((((obj)->value_).gc))))->gc)),(&(((union GCUnion *)((mt)))->gc))) : ((void)((0))));
        luaC_checkfinalizer(L, (((obj)->value_).gc), mt);
      }
      break;
    }
    case 7: {
      ((&((((union GCUnion *)((((obj)->value_).gc))))->u)))->metatable = mt;
      if (mt) {
        ( ((((((&((((union GCUnion *)((((obj)->value_).gc))))->u))))->marked) & ((1<<(5)))) && (((mt)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(&(((union GCUnion *)((((&((((union GCUnion *)((((obj)->value_).gc))))->u))))))->gc)),(&(((union GCUnion *)((mt)))->gc))) : ((void)((0))));
        luaC_checkfinalizer(L, (((obj)->value_).gc), mt);
      }
      break;
    }
    default: {
      (L->l_G)->mt[(((((obj)->tt_)) & 0x0F))] = mt;
      break;
    }
  }
  L->top--;
  ((void) 0);
  return 1;
}
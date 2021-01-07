
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



extern void abort();
extern  panic;
extern void luaD_seterrorobj(lua_State *, int, StkId);
extern void luaD_throw(lua_State *, int);
extern int luaF_close(lua_State *, StkId, int);
extern void longjmp(struct __jmp_buf_tag *, int);

void __attribute__((noreturn)) luaD_throw (lua_State *L, int errcode) {
  if (L->errorJmp) {
    L->errorJmp->status = errcode;
    longjmp((L->errorJmp)->b, 1);
  }
  else {
    global_State *g = (L->l_G);
    errcode = luaF_close(L, L->stack, errcode);
    L->status = ((lu_byte)((errcode)));
    if (g->mainthread->errorJmp) {
      { TValue *io1=((&(g->mainthread->top++)->val)); const TValue *io2=((&(L->top - 1)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
      luaD_throw(g->mainthread, errcode);
    }
    else {
      if (g->panic) {
        luaD_seterrorobj(L, errcode, L->top);
        if (L->ci->top < L->top)
          L->ci->top = L->top;
        ((void) 0);
        g->panic(L);
      }
      abort();
    }
  }
}
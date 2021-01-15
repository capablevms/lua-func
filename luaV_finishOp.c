
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

void luaV_finishOp (lua_State *L) {
  CallInfo *ci = L->ci;
  StkId base = ci->func + 1;
  Instruction inst = *(ci->u.l.savedpc - 1);
  OpCode op = (((OpCode)(((inst)>>0) & ((~((~(Instruction)0)<<(7)))<<(0)))));
  switch (op) {
    case OP_MMBIN: case OP_MMBINI: case OP_MMBINK: {
      { TValue *io1=((&(base + (((int)((((*(ci->u.l.savedpc - 2))>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))->val)); const TValue *io2=((&(--L->top)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
      break;
    }
    case OP_UNM: case OP_BNOT: case OP_LEN:
    case OP_GETTABUP: case OP_GETTABLE: case OP_GETI:
    case OP_GETFIELD: case OP_SELF: {
      { TValue *io1=((&(base + (((int)((((inst)>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))->val)); const TValue *io2=((&(--L->top)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
      break;
    }
    case OP_LT: case OP_LE:
    case OP_LTI: case OP_LEI:
    case OP_GTI: case OP_GEI:
    case OP_EQ: {
      int res = !((((((&(L->top - 1)->val)))->tt_) == (((1) | ((0) << 4)))) || ((((((((&(L->top - 1)->val)))->tt_)) & 0x0F)) == (0)));
      L->top--;






      ((void)0);
      if (res != ((((int)((((inst)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<(1)))<<(0))))))))
        ci->u.l.savedpc++;
      break;
    }
    case OP_CONCAT: {
      StkId top = L->top - 1;
      int a = (((int)((((inst)>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0))))));
      int total = ((int)((top - 1 - (base + a))));
      { TValue *io1=((&(top - 2)->val)); const TValue *io2=((&(top)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
      L->top = top - 1;
      luaV_concat(L, total);
      break;
    }
    default: {

      ((void)0);


      break;
    }
  }
}

#include<math.h>
#include<string.h>

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

extern void pushclosure (lua_State *, Proto *, UpVal **, StkId, StkId);
extern int LTnum (const TValue *, const TValue *);
extern int LEnum (const TValue *, const TValue *);
extern int floatforloop (StkId);
extern int forprep (lua_State *, StkId);
extern int lessthanothers (lua_State *, const TValue *, const TValue *);
extern int lessequalothers (lua_State *, const TValue *, const TValue *);

void luaV_execute (lua_State *L, CallInfo *ci) {
  LClosure *cl;
  TValue *k;
  StkId base;
  const Instruction *pc;
  int trap;



 execute:
  trap = L->hookmask;
  cl = ((&((((union GCUnion *)(((((&(ci->func)->val))->value_).gc))))->cl.l)));
  k = cl->p->k;
  pc = ci->u.l.savedpc;
  if (trap) {
    if (cl->p->is_vararg)
      trap = 0;
    else if (pc == cl->p->code)
      luaD_hookcall(L, ci);
    ci->u.l.trap = 1;
  }
  base = ci->func + 1;

  for (;;) {
    Instruction i;
    StkId ra;
    { if (trap) { trap = luaG_traceexec(L, pc); (base = ci->func + 1); } i = *(pc++); ra = (base+(((int)((((i)>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0))))))); };
    ((void)0);
    ((void)0);

    ((void)0);
    switch((((OpCode)(((i)>>0) & ((~((~(Instruction)0)<<(7)))<<(0)))))) {
      case OP_MOVE: {
        { TValue *io1=((&(ra)->val)); const TValue *io2=((&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
        break;
      }
      case OP_LOADI: {
        lua_Integer b = ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<((8 + 8 + 1))))<<(0)))))) - (((1<<(8 + 8 + 1))-1)>>1));
        { TValue *io=((&(ra)->val)); ((io)->value_).i=(b); ((io)->tt_=(((3) | ((0) << 4)))); };
        break;
      }
      case OP_LOADF: {
        int b = ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<((8 + 8 + 1))))<<(0)))))) - (((1<<(8 + 8 + 1))-1)>>1));
        { TValue *io=((&(ra)->val)); ((io)->value_).n=(((lua_Number)((b)))); ((io)->tt_=(((3) | ((1) << 4)))); };
        break;
      }
      case OP_LOADK: {
        TValue *rb = k + ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<((8 + 8 + 1))))<<(0)))))));
        { TValue *io1=((&(ra)->val)); const TValue *io2=(rb); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
        break;
      }
      case OP_LOADKX: {
        TValue *rb;
        rb = k + ((((int)((((*pc)>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0))))))); pc++;
        { TValue *io1=((&(ra)->val)); const TValue *io2=(rb); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
        break;
      }
      case OP_LOADFALSE: {
        (((&(ra)->val))->tt_=(((1) | ((0) << 4))));
        break;
      }
      case OP_LFALSESKIP: {
        (((&(ra)->val))->tt_=(((1) | ((0) << 4))));
        pc++;
        break;
      }
      case OP_LOADTRUE: {
        (((&(ra)->val))->tt_=(((1) | ((1) << 4))));
        break;
      }
      case OP_LOADNIL: {
        int b = ((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        do {
          (((&(ra++)->val))->tt_=(((0) | ((0) << 4))));
        } while (b--);
        break;
      }
      case OP_GETUPVAL: {
        int b = ((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        { TValue *io1=((&(ra)->val)); const TValue *io2=(cl->upvals[b]->v); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
        break;
      }
      case OP_SETUPVAL: {
        UpVal *uv = cl->upvals[((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))];
        { TValue *io1=(uv->v); const TValue *io2=((&(ra)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
        ( (((((&(ra)->val))->tt_) & (1 << 6)) && (((uv)->marked) & ((1<<(5)))) && (((((((&(ra)->val))->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(&(((union GCUnion *)((uv)))->gc)),((((&(ra)->val))->value_).gc)) : ((void)((0))));
        break;
      }
      case OP_GETTABUP: {
        const TValue *slot;
        TValue *upval = cl->upvals[((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))]->v;
        TValue *rc = (k+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))));
        TString *key = ((&((((union GCUnion *)((((rc)->value_).gc))))->ts)));
        if ((!((((upval))->tt_) == (((((5) | ((0) << 4))) | (1 << 6)))) ? (slot = ((void*)0), 0) : (slot = luaH_getshortstr(((&((((union GCUnion *)((((upval)->value_).gc))))->h))), key), !(((((((slot))->tt_)) & 0x0F)) == (0))))) {
          { TValue *io1=((&(ra)->val)); const TValue *io2=(slot); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
        }
        else
          (((ci->u.l.savedpc = pc), L->top = ci->top), (luaV_finishget(L, upval, rc, ra, slot)), (trap = ci->u.l.trap));
        break;
      }
      case OP_GETTABLE: {
        const TValue *slot;
        TValue *rb = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val);
        TValue *rc = (&((base+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val);
        lua_Unsigned n;
        if (((((rc))->tt_) == (((3) | ((0) << 4))))
            ? (((void)((n = (((rc)->value_).i)))), (!((((rb))->tt_) == (((((5) | ((0) << 4))) | (1 << 6)))) ? (slot = ((void*)0), 0) : (slot = (((lua_Unsigned)(n)) - 1u < ((&((((union GCUnion *)((((rb)->value_).gc))))->h)))->alimit) ? &((&((((union GCUnion *)((((rb)->value_).gc))))->h)))->array[n - 1] : luaH_getint(((&((((union GCUnion *)((((rb)->value_).gc))))->h))), n), !(((((((slot))->tt_)) & 0x0F)) == (0)))))
            : (!((((rb))->tt_) == (((((5) | ((0) << 4))) | (1 << 6)))) ? (slot = ((void*)0), 0) : (slot = luaH_get(((&((((union GCUnion *)((((rb)->value_).gc))))->h))), rc), !(((((((slot))->tt_)) & 0x0F)) == (0))))) {
          { TValue *io1=((&(ra)->val)); const TValue *io2=(slot); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
        }
        else
          (((ci->u.l.savedpc = pc), L->top = ci->top), (luaV_finishget(L, rb, rc, ra, slot)), (trap = ci->u.l.trap));
        break;
      }
      case OP_GETI: {
        const TValue *slot;
        TValue *rb = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val);
        int c = ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        if ((!((((rb))->tt_) == (((((5) | ((0) << 4))) | (1 << 6)))) ? (slot = ((void*)0), 0) : (slot = (((lua_Unsigned)(c)) - 1u < ((&((((union GCUnion *)((((rb)->value_).gc))))->h)))->alimit) ? &((&((((union GCUnion *)((((rb)->value_).gc))))->h)))->array[c - 1] : luaH_getint(((&((((union GCUnion *)((((rb)->value_).gc))))->h))), c), !(((((((slot))->tt_)) & 0x0F)) == (0))))) {
          { TValue *io1=((&(ra)->val)); const TValue *io2=(slot); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
        }
        else {
          TValue key;
          { TValue *io=(&key); ((io)->value_).i=(c); ((io)->tt_=(((3) | ((0) << 4)))); };
          (((ci->u.l.savedpc = pc), L->top = ci->top), (luaV_finishget(L, rb, &key, ra, slot)), (trap = ci->u.l.trap));
        }
        break;
      }
      case OP_GETFIELD: {
        const TValue *slot;
        TValue *rb = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val);
        TValue *rc = (k+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))));
        TString *key = ((&((((union GCUnion *)((((rc)->value_).gc))))->ts)));
        if ((!((((rb))->tt_) == (((((5) | ((0) << 4))) | (1 << 6)))) ? (slot = ((void*)0), 0) : (slot = luaH_getshortstr(((&((((union GCUnion *)((((rb)->value_).gc))))->h))), key), !(((((((slot))->tt_)) & 0x0F)) == (0))))) {
          { TValue *io1=((&(ra)->val)); const TValue *io2=(slot); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
        }
        else
          (((ci->u.l.savedpc = pc), L->top = ci->top), (luaV_finishget(L, rb, rc, ra, slot)), (trap = ci->u.l.trap));
        break;
      }
      case OP_SETTABUP: {
        const TValue *slot;
        TValue *upval = cl->upvals[(((int)((((i)>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0))))))]->v;
        TValue *rb = (k+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0))))))));
        TValue *rc = ((((((int)((((i) & (1u << ((0 + 7) + 8))))))))) ? k + ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))) : (&(base + ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))))->val));
        TString *key = ((&((((union GCUnion *)((((rb)->value_).gc))))->ts)));
        if ((!((((upval))->tt_) == (((((5) | ((0) << 4))) | (1 << 6)))) ? (slot = ((void*)0), 0) : (slot = luaH_getshortstr(((&((((union GCUnion *)((((upval)->value_).gc))))->h))), key), !(((((((slot))->tt_)) & 0x0F)) == (0))))) {
          { { TValue *io1=(((TValue *)(slot))); const TValue *io2=(rc); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); }; ( ((((rc)->tt_) & (1 << 6)) && ((((((upval)->value_).gc))->marked) & ((1<<(5)))) && ((((((rc)->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrierback_(L,(((upval)->value_).gc)) : ((void)((0)))); };
        }
        else
          (((ci->u.l.savedpc = pc), L->top = ci->top), (luaV_finishset(L, upval, rb, rc, slot)), (trap = ci->u.l.trap));
        break;
      }
      case OP_SETTABLE: {
        const TValue *slot;
        TValue *rb = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val);
        TValue *rc = ((((((int)((((i) & (1u << ((0 + 7) + 8))))))))) ? k + ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))) : (&(base + ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))))->val));
        lua_Unsigned n;
        if (((((rb))->tt_) == (((3) | ((0) << 4))))
            ? (((void)((n = (((rb)->value_).i)))), (!(((((&(ra)->val)))->tt_) == (((((5) | ((0) << 4))) | (1 << 6)))) ? (slot = ((void*)0), 0) : (slot = (((lua_Unsigned)(n)) - 1u < ((&((((union GCUnion *)(((((&(ra)->val))->value_).gc))))->h)))->alimit) ? &((&((((union GCUnion *)(((((&(ra)->val))->value_).gc))))->h)))->array[n - 1] : luaH_getint(((&((((union GCUnion *)(((((&(ra)->val))->value_).gc))))->h))), n), !(((((((slot))->tt_)) & 0x0F)) == (0)))))
            : (!(((((&(ra)->val)))->tt_) == (((((5) | ((0) << 4))) | (1 << 6)))) ? (slot = ((void*)0), 0) : (slot = luaH_get(((&((((union GCUnion *)(((((&(ra)->val))->value_).gc))))->h))), rb), !(((((((slot))->tt_)) & 0x0F)) == (0))))) {
          { { TValue *io1=(((TValue *)(slot))); const TValue *io2=(rc); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); }; ( ((((rc)->tt_) & (1 << 6)) && (((((((&(ra)->val))->value_).gc))->marked) & ((1<<(5)))) && ((((((rc)->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrierback_(L,((((&(ra)->val))->value_).gc)) : ((void)((0)))); };
        }
        else
          (((ci->u.l.savedpc = pc), L->top = ci->top), (luaV_finishset(L, (&(ra)->val), rb, rc, slot)), (trap = ci->u.l.trap));
        break;
      }
      case OP_SETI: {
        const TValue *slot;
        int c = ((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        TValue *rc = ((((((int)((((i) & (1u << ((0 + 7) + 8))))))))) ? k + ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))) : (&(base + ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))))->val));
        if ((!(((((&(ra)->val)))->tt_) == (((((5) | ((0) << 4))) | (1 << 6)))) ? (slot = ((void*)0), 0) : (slot = (((lua_Unsigned)(c)) - 1u < ((&((((union GCUnion *)(((((&(ra)->val))->value_).gc))))->h)))->alimit) ? &((&((((union GCUnion *)(((((&(ra)->val))->value_).gc))))->h)))->array[c - 1] : luaH_getint(((&((((union GCUnion *)(((((&(ra)->val))->value_).gc))))->h))), c), !(((((((slot))->tt_)) & 0x0F)) == (0))))) {
          { { TValue *io1=(((TValue *)(slot))); const TValue *io2=(rc); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); }; ( ((((rc)->tt_) & (1 << 6)) && (((((((&(ra)->val))->value_).gc))->marked) & ((1<<(5)))) && ((((((rc)->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrierback_(L,((((&(ra)->val))->value_).gc)) : ((void)((0)))); };
        }
        else {
          TValue key;
          { TValue *io=(&key); ((io)->value_).i=(c); ((io)->tt_=(((3) | ((0) << 4)))); };
          (((ci->u.l.savedpc = pc), L->top = ci->top), (luaV_finishset(L, (&(ra)->val), &key, rc, slot)), (trap = ci->u.l.trap));
        }
        break;
      }
      case OP_SETFIELD: {
        const TValue *slot;
        TValue *rb = (k+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0))))))));
        TValue *rc = ((((((int)((((i) & (1u << ((0 + 7) + 8))))))))) ? k + ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))) : (&(base + ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))))->val));
        TString *key = ((&((((union GCUnion *)((((rb)->value_).gc))))->ts)));
        if ((!(((((&(ra)->val)))->tt_) == (((((5) | ((0) << 4))) | (1 << 6)))) ? (slot = ((void*)0), 0) : (slot = luaH_getshortstr(((&((((union GCUnion *)(((((&(ra)->val))->value_).gc))))->h))), key), !(((((((slot))->tt_)) & 0x0F)) == (0))))) {
          { { TValue *io1=(((TValue *)(slot))); const TValue *io2=(rc); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); }; ( ((((rc)->tt_) & (1 << 6)) && (((((((&(ra)->val))->value_).gc))->marked) & ((1<<(5)))) && ((((((rc)->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrierback_(L,((((&(ra)->val))->value_).gc)) : ((void)((0)))); };
        }
        else
          (((ci->u.l.savedpc = pc), L->top = ci->top), (luaV_finishset(L, (&(ra)->val), rb, rc, slot)), (trap = ci->u.l.trap));
        break;
      }
      case OP_NEWTABLE: {
        int b = ((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        int c = ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        Table *t;
        if (b > 0)
          b = 1 << (b - 1);
        ((void)0);
        if (((((int)((((i) & (1u << ((0 + 7) + 8)))))))))
          c += ((((int)((((*pc)>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0))))))) * (((1<<8)-1) + 1);
        pc++;
        L->top = ra + 1;
        t = luaH_new(L);
        { TValue *io = ((&(ra)->val)); Table *x_ = (t); ((io)->value_).gc = (&(((union GCUnion *)((x_)))->gc)); ((io)->tt_=(((((5) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
        if (b != 0 || c != 0)
          luaH_resize(L, t, c, b);
        { { if ((L->l_G)->GCdebt > 0) { ((ci->u.l.savedpc = pc), L->top = (ra + 1)); luaC_step(L); (trap = ci->u.l.trap);}; ((void)0); }; {((void) 0); ((void) 0);}; };
        break;
      }
      case OP_SELF: {
        const TValue *slot;
        TValue *rb = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val);
        TValue *rc = ((((((int)((((i) & (1u << ((0 + 7) + 8))))))))) ? k + ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))) : (&(base + ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))))->val));
        TString *key = ((&((((union GCUnion *)((((rc)->value_).gc))))->ts)));
        { TValue *io1=((&(ra + 1)->val)); const TValue *io2=(rb); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
        if ((!((((rb))->tt_) == (((((5) | ((0) << 4))) | (1 << 6)))) ? (slot = ((void*)0), 0) : (slot = luaH_getstr(((&((((union GCUnion *)((((rb)->value_).gc))))->h))), key), !(((((((slot))->tt_)) & 0x0F)) == (0))))) {
          { TValue *io1=((&(ra)->val)); const TValue *io2=(slot); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
        }
        else
          (((ci->u.l.savedpc = pc), L->top = ci->top), (luaV_finishget(L, rb, rc, ra, slot)), (trap = ci->u.l.trap));
        break;
      }
      case OP_ADDI: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); int imm = ((((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))) - (((1<<8)-1) >> 1)); if (((((v1))->tt_) == (((3) | ((0) << 4))))) { lua_Integer iv1 = (((v1)->value_).i); pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(((lua_Integer)(((lua_Unsigned)(iv1)) + ((lua_Unsigned)(imm))))); ((io)->tt_=(((3) | ((0) << 4)))); }; } else if (((((v1))->tt_) == (((3) | ((1) << 4))))) { lua_Number nb = (((v1)->value_).n); lua_Number fimm = ((lua_Number)((imm))); pc++; { TValue *io=((&(ra)->val)); ((io)->value_).n=(((nb)+(fimm))); ((io)->tt_=(((3) | ((1) << 4)))); }; }};
        break;
      }
      case OP_ADDK: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (k+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))); { if (((((v1))->tt_) == (((3) | ((0) << 4)))) && ((((v2))->tt_) == (((3) | ((0) << 4))))) { lua_Integer i1 = (((v1)->value_).i); lua_Integer i2 = (((v2)->value_).i); pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(((lua_Integer)(((lua_Unsigned)(i1)) + ((lua_Unsigned)(i2))))); ((io)->tt_=(((3) | ((0) << 4)))); }; } else { lua_Number n1; lua_Number n2; if ((((((v1))->tt_) == (((3) | ((1) << 4)))) ? ((n1) = (((v1)->value_).n), 1) : (((((v1))->tt_) == (((3) | ((0) << 4)))) ? ((n1) = ((lua_Number)(((((v1)->value_).i)))), 1) : 0)) && (((((v2))->tt_) == (((3) | ((1) << 4)))) ? ((n2) = (((v2)->value_).n), 1) : (((((v2))->tt_) == (((3) | ((0) << 4)))) ? ((n2) = ((lua_Number)(((((v2)->value_).i)))), 1) : 0))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).n=(((n1)+(n2))); ((io)->tt_=(((3) | ((1) << 4)))); }; }}; }; };
        break;
      }
      case OP_SUBK: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (k+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))); { if (((((v1))->tt_) == (((3) | ((0) << 4)))) && ((((v2))->tt_) == (((3) | ((0) << 4))))) { lua_Integer i1 = (((v1)->value_).i); lua_Integer i2 = (((v2)->value_).i); pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(((lua_Integer)(((lua_Unsigned)(i1)) - ((lua_Unsigned)(i2))))); ((io)->tt_=(((3) | ((0) << 4)))); }; } else { lua_Number n1; lua_Number n2; if ((((((v1))->tt_) == (((3) | ((1) << 4)))) ? ((n1) = (((v1)->value_).n), 1) : (((((v1))->tt_) == (((3) | ((0) << 4)))) ? ((n1) = ((lua_Number)(((((v1)->value_).i)))), 1) : 0)) && (((((v2))->tt_) == (((3) | ((1) << 4)))) ? ((n2) = (((v2)->value_).n), 1) : (((((v2))->tt_) == (((3) | ((0) << 4)))) ? ((n2) = ((lua_Number)(((((v2)->value_).i)))), 1) : 0))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).n=(((n1)-(n2))); ((io)->tt_=(((3) | ((1) << 4)))); }; }}; }; };
        break;
      }
      case OP_MULK: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (k+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))); { if (((((v1))->tt_) == (((3) | ((0) << 4)))) && ((((v2))->tt_) == (((3) | ((0) << 4))))) { lua_Integer i1 = (((v1)->value_).i); lua_Integer i2 = (((v2)->value_).i); pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(((lua_Integer)(((lua_Unsigned)(i1)) * ((lua_Unsigned)(i2))))); ((io)->tt_=(((3) | ((0) << 4)))); }; } else { lua_Number n1; lua_Number n2; if ((((((v1))->tt_) == (((3) | ((1) << 4)))) ? ((n1) = (((v1)->value_).n), 1) : (((((v1))->tt_) == (((3) | ((0) << 4)))) ? ((n1) = ((lua_Number)(((((v1)->value_).i)))), 1) : 0)) && (((((v2))->tt_) == (((3) | ((1) << 4)))) ? ((n2) = (((v2)->value_).n), 1) : (((((v2))->tt_) == (((3) | ((0) << 4)))) ? ((n2) = ((lua_Number)(((((v2)->value_).i)))), 1) : 0))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).n=(((n1)*(n2))); ((io)->tt_=(((3) | ((1) << 4)))); }; }}; }; };
        break;
      }
      case OP_MODK: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (k+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))); { if (((((v1))->tt_) == (((3) | ((0) << 4)))) && ((((v2))->tt_) == (((3) | ((0) << 4))))) { lua_Integer i1 = (((v1)->value_).i); lua_Integer i2 = (((v2)->value_).i); pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(luaV_mod(L, i1, i2)); ((io)->tt_=(((3) | ((0) << 4)))); }; } else { lua_Number n1; lua_Number n2; if ((((((v1))->tt_) == (((3) | ((1) << 4)))) ? ((n1) = (((v1)->value_).n), 1) : (((((v1))->tt_) == (((3) | ((0) << 4)))) ? ((n1) = ((lua_Number)(((((v1)->value_).i)))), 1) : 0)) && (((((v2))->tt_) == (((3) | ((1) << 4)))) ? ((n2) = (((v2)->value_).n), 1) : (((((v2))->tt_) == (((3) | ((0) << 4)))) ? ((n2) = ((lua_Number)(((((v2)->value_).i)))), 1) : 0))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).n=(luaV_modf(L, n1, n2)); ((io)->tt_=(((3) | ((1) << 4)))); }; }}; }; };
        break;
      }
      case OP_POWK: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (k+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))); { lua_Number n1; lua_Number n2; if ((((((v1))->tt_) == (((3) | ((1) << 4)))) ? ((n1) = (((v1)->value_).n), 1) : (((((v1))->tt_) == (((3) | ((0) << 4)))) ? ((n1) = ((lua_Number)(((((v1)->value_).i)))), 1) : 0)) && (((((v2))->tt_) == (((3) | ((1) << 4)))) ? ((n2) = (((v2)->value_).n), 1) : (((((v2))->tt_) == (((3) | ((0) << 4)))) ? ((n2) = ((lua_Number)(((((v2)->value_).i)))), 1) : 0))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).n=(((void)L, pow(n1,n2))); ((io)->tt_=(((3) | ((1) << 4)))); }; }}; };
        break;
      }
      case OP_DIVK: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (k+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))); { lua_Number n1; lua_Number n2; if ((((((v1))->tt_) == (((3) | ((1) << 4)))) ? ((n1) = (((v1)->value_).n), 1) : (((((v1))->tt_) == (((3) | ((0) << 4)))) ? ((n1) = ((lua_Number)(((((v1)->value_).i)))), 1) : 0)) && (((((v2))->tt_) == (((3) | ((1) << 4)))) ? ((n2) = (((v2)->value_).n), 1) : (((((v2))->tt_) == (((3) | ((0) << 4)))) ? ((n2) = ((lua_Number)(((((v2)->value_).i)))), 1) : 0))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).n=(((n1)/(n2))); ((io)->tt_=(((3) | ((1) << 4)))); }; }}; };
        break;
      }
      case OP_IDIVK: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (k+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))); { if (((((v1))->tt_) == (((3) | ((0) << 4)))) && ((((v2))->tt_) == (((3) | ((0) << 4))))) { lua_Integer i1 = (((v1)->value_).i); lua_Integer i2 = (((v2)->value_).i); pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(luaV_idiv(L, i1, i2)); ((io)->tt_=(((3) | ((0) << 4)))); }; } else { lua_Number n1; lua_Number n2; if ((((((v1))->tt_) == (((3) | ((1) << 4)))) ? ((n1) = (((v1)->value_).n), 1) : (((((v1))->tt_) == (((3) | ((0) << 4)))) ? ((n1) = ((lua_Number)(((((v1)->value_).i)))), 1) : 0)) && (((((v2))->tt_) == (((3) | ((1) << 4)))) ? ((n2) = (((v2)->value_).n), 1) : (((((v2))->tt_) == (((3) | ((0) << 4)))) ? ((n2) = ((lua_Number)(((((v2)->value_).i)))), 1) : 0))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).n=(((void)L, (floor(((n1)/(n2)))))); ((io)->tt_=(((3) | ((1) << 4)))); }; }}; }; };
        break;
      }
      case OP_BANDK: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (k+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))); lua_Integer i1; lua_Integer i2 = (((v2)->value_).i); if ((((((v1))->tt_) == (((3) | ((0) << 4)))) ? (*(&i1) = (((v1)->value_).i), 1) : luaV_tointegerns(v1,&i1,F2Ieq))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(((lua_Integer)(((lua_Unsigned)(i1)) & ((lua_Unsigned)(i2))))); ((io)->tt_=(((3) | ((0) << 4)))); }; }};
        break;
      }
      case OP_BORK: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (k+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))); lua_Integer i1; lua_Integer i2 = (((v2)->value_).i); if ((((((v1))->tt_) == (((3) | ((0) << 4)))) ? (*(&i1) = (((v1)->value_).i), 1) : luaV_tointegerns(v1,&i1,F2Ieq))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(((lua_Integer)(((lua_Unsigned)(i1)) | ((lua_Unsigned)(i2))))); ((io)->tt_=(((3) | ((0) << 4)))); }; }};
        break;
      }
      case OP_BXORK: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (k+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))); lua_Integer i1; lua_Integer i2 = (((v2)->value_).i); if ((((((v1))->tt_) == (((3) | ((0) << 4)))) ? (*(&i1) = (((v1)->value_).i), 1) : luaV_tointegerns(v1,&i1,F2Ieq))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(((lua_Integer)(((lua_Unsigned)(i1)) ^ ((lua_Unsigned)(i2))))); ((io)->tt_=(((3) | ((0) << 4)))); }; }};
        break;
      }
      case OP_SHRI: {
        TValue *rb = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val);
        int ic = ((((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))) - (((1<<8)-1) >> 1));
        lua_Integer ib;
        if ((((((rb))->tt_) == (((3) | ((0) << 4)))) ? (*(&ib) = (((rb)->value_).i), 1) : luaV_tointegerns(rb,&ib,F2Ieq))) {
          pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(luaV_shiftl(ib, -ic)); ((io)->tt_=(((3) | ((0) << 4)))); };
        }
        break;
      }
      case OP_SHLI: {
        TValue *rb = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val);
        int ic = ((((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))) - (((1<<8)-1) >> 1));
        lua_Integer ib;
        if ((((((rb))->tt_) == (((3) | ((0) << 4)))) ? (*(&ib) = (((rb)->value_).i), 1) : luaV_tointegerns(rb,&ib,F2Ieq))) {
          pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(luaV_shiftl(ic, ib)); ((io)->tt_=(((3) | ((0) << 4)))); };
        }
        break;
      }
      case OP_ADD: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (&((base+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); { if (((((v1))->tt_) == (((3) | ((0) << 4)))) && ((((v2))->tt_) == (((3) | ((0) << 4))))) { lua_Integer i1 = (((v1)->value_).i); lua_Integer i2 = (((v2)->value_).i); pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(((lua_Integer)(((lua_Unsigned)(i1)) + ((lua_Unsigned)(i2))))); ((io)->tt_=(((3) | ((0) << 4)))); }; } else { lua_Number n1; lua_Number n2; if ((((((v1))->tt_) == (((3) | ((1) << 4)))) ? ((n1) = (((v1)->value_).n), 1) : (((((v1))->tt_) == (((3) | ((0) << 4)))) ? ((n1) = ((lua_Number)(((((v1)->value_).i)))), 1) : 0)) && (((((v2))->tt_) == (((3) | ((1) << 4)))) ? ((n2) = (((v2)->value_).n), 1) : (((((v2))->tt_) == (((3) | ((0) << 4)))) ? ((n2) = ((lua_Number)(((((v2)->value_).i)))), 1) : 0))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).n=(((n1)+(n2))); ((io)->tt_=(((3) | ((1) << 4)))); }; }}; }; };
        break;
      }
      case OP_SUB: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (&((base+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); { if (((((v1))->tt_) == (((3) | ((0) << 4)))) && ((((v2))->tt_) == (((3) | ((0) << 4))))) { lua_Integer i1 = (((v1)->value_).i); lua_Integer i2 = (((v2)->value_).i); pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(((lua_Integer)(((lua_Unsigned)(i1)) - ((lua_Unsigned)(i2))))); ((io)->tt_=(((3) | ((0) << 4)))); }; } else { lua_Number n1; lua_Number n2; if ((((((v1))->tt_) == (((3) | ((1) << 4)))) ? ((n1) = (((v1)->value_).n), 1) : (((((v1))->tt_) == (((3) | ((0) << 4)))) ? ((n1) = ((lua_Number)(((((v1)->value_).i)))), 1) : 0)) && (((((v2))->tt_) == (((3) | ((1) << 4)))) ? ((n2) = (((v2)->value_).n), 1) : (((((v2))->tt_) == (((3) | ((0) << 4)))) ? ((n2) = ((lua_Number)(((((v2)->value_).i)))), 1) : 0))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).n=(((n1)-(n2))); ((io)->tt_=(((3) | ((1) << 4)))); }; }}; }; };
        break;
      }
      case OP_MUL: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (&((base+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); { if (((((v1))->tt_) == (((3) | ((0) << 4)))) && ((((v2))->tt_) == (((3) | ((0) << 4))))) { lua_Integer i1 = (((v1)->value_).i); lua_Integer i2 = (((v2)->value_).i); pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(((lua_Integer)(((lua_Unsigned)(i1)) * ((lua_Unsigned)(i2))))); ((io)->tt_=(((3) | ((0) << 4)))); }; } else { lua_Number n1; lua_Number n2; if ((((((v1))->tt_) == (((3) | ((1) << 4)))) ? ((n1) = (((v1)->value_).n), 1) : (((((v1))->tt_) == (((3) | ((0) << 4)))) ? ((n1) = ((lua_Number)(((((v1)->value_).i)))), 1) : 0)) && (((((v2))->tt_) == (((3) | ((1) << 4)))) ? ((n2) = (((v2)->value_).n), 1) : (((((v2))->tt_) == (((3) | ((0) << 4)))) ? ((n2) = ((lua_Number)(((((v2)->value_).i)))), 1) : 0))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).n=(((n1)*(n2))); ((io)->tt_=(((3) | ((1) << 4)))); }; }}; }; };
        break;
      }
      case OP_MOD: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (&((base+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); { if (((((v1))->tt_) == (((3) | ((0) << 4)))) && ((((v2))->tt_) == (((3) | ((0) << 4))))) { lua_Integer i1 = (((v1)->value_).i); lua_Integer i2 = (((v2)->value_).i); pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(luaV_mod(L, i1, i2)); ((io)->tt_=(((3) | ((0) << 4)))); }; } else { lua_Number n1; lua_Number n2; if ((((((v1))->tt_) == (((3) | ((1) << 4)))) ? ((n1) = (((v1)->value_).n), 1) : (((((v1))->tt_) == (((3) | ((0) << 4)))) ? ((n1) = ((lua_Number)(((((v1)->value_).i)))), 1) : 0)) && (((((v2))->tt_) == (((3) | ((1) << 4)))) ? ((n2) = (((v2)->value_).n), 1) : (((((v2))->tt_) == (((3) | ((0) << 4)))) ? ((n2) = ((lua_Number)(((((v2)->value_).i)))), 1) : 0))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).n=(luaV_modf(L, n1, n2)); ((io)->tt_=(((3) | ((1) << 4)))); }; }}; }; };
        break;
      }
      case OP_POW: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (&((base+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); { lua_Number n1; lua_Number n2; if ((((((v1))->tt_) == (((3) | ((1) << 4)))) ? ((n1) = (((v1)->value_).n), 1) : (((((v1))->tt_) == (((3) | ((0) << 4)))) ? ((n1) = ((lua_Number)(((((v1)->value_).i)))), 1) : 0)) && (((((v2))->tt_) == (((3) | ((1) << 4)))) ? ((n2) = (((v2)->value_).n), 1) : (((((v2))->tt_) == (((3) | ((0) << 4)))) ? ((n2) = ((lua_Number)(((((v2)->value_).i)))), 1) : 0))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).n=(((void)L, pow(n1,n2))); ((io)->tt_=(((3) | ((1) << 4)))); }; }}; };
        break;
      }
      case OP_DIV: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (&((base+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); { lua_Number n1; lua_Number n2; if ((((((v1))->tt_) == (((3) | ((1) << 4)))) ? ((n1) = (((v1)->value_).n), 1) : (((((v1))->tt_) == (((3) | ((0) << 4)))) ? ((n1) = ((lua_Number)(((((v1)->value_).i)))), 1) : 0)) && (((((v2))->tt_) == (((3) | ((1) << 4)))) ? ((n2) = (((v2)->value_).n), 1) : (((((v2))->tt_) == (((3) | ((0) << 4)))) ? ((n2) = ((lua_Number)(((((v2)->value_).i)))), 1) : 0))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).n=(((n1)/(n2))); ((io)->tt_=(((3) | ((1) << 4)))); }; }}; };
        break;
      }
      case OP_IDIV: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (&((base+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); { if (((((v1))->tt_) == (((3) | ((0) << 4)))) && ((((v2))->tt_) == (((3) | ((0) << 4))))) { lua_Integer i1 = (((v1)->value_).i); lua_Integer i2 = (((v2)->value_).i); pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(luaV_idiv(L, i1, i2)); ((io)->tt_=(((3) | ((0) << 4)))); }; } else { lua_Number n1; lua_Number n2; if ((((((v1))->tt_) == (((3) | ((1) << 4)))) ? ((n1) = (((v1)->value_).n), 1) : (((((v1))->tt_) == (((3) | ((0) << 4)))) ? ((n1) = ((lua_Number)(((((v1)->value_).i)))), 1) : 0)) && (((((v2))->tt_) == (((3) | ((1) << 4)))) ? ((n2) = (((v2)->value_).n), 1) : (((((v2))->tt_) == (((3) | ((0) << 4)))) ? ((n2) = ((lua_Number)(((((v2)->value_).i)))), 1) : 0))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).n=(((void)L, (floor(((n1)/(n2)))))); ((io)->tt_=(((3) | ((1) << 4)))); }; }}; }; };
        break;
      }
      case OP_BAND: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (&((base+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); lua_Integer i1; lua_Integer i2; if ((((((v1))->tt_) == (((3) | ((0) << 4)))) ? (*(&i1) = (((v1)->value_).i), 1) : luaV_tointegerns(v1,&i1,F2Ieq)) && (((((v2))->tt_) == (((3) | ((0) << 4)))) ? (*(&i2) = (((v2)->value_).i), 1) : luaV_tointegerns(v2,&i2,F2Ieq))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(((lua_Integer)(((lua_Unsigned)(i1)) & ((lua_Unsigned)(i2))))); ((io)->tt_=(((3) | ((0) << 4)))); }; }};
        break;
      }
      case OP_BOR: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (&((base+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); lua_Integer i1; lua_Integer i2; if ((((((v1))->tt_) == (((3) | ((0) << 4)))) ? (*(&i1) = (((v1)->value_).i), 1) : luaV_tointegerns(v1,&i1,F2Ieq)) && (((((v2))->tt_) == (((3) | ((0) << 4)))) ? (*(&i2) = (((v2)->value_).i), 1) : luaV_tointegerns(v2,&i2,F2Ieq))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(((lua_Integer)(((lua_Unsigned)(i1)) | ((lua_Unsigned)(i2))))); ((io)->tt_=(((3) | ((0) << 4)))); }; }};
        break;
      }
      case OP_BXOR: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (&((base+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); lua_Integer i1; lua_Integer i2; if ((((((v1))->tt_) == (((3) | ((0) << 4)))) ? (*(&i1) = (((v1)->value_).i), 1) : luaV_tointegerns(v1,&i1,F2Ieq)) && (((((v2))->tt_) == (((3) | ((0) << 4)))) ? (*(&i2) = (((v2)->value_).i), 1) : luaV_tointegerns(v2,&i2,F2Ieq))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(((lua_Integer)(((lua_Unsigned)(i1)) ^ ((lua_Unsigned)(i2))))); ((io)->tt_=(((3) | ((0) << 4)))); }; }};
        break;
      }
      case OP_SHR: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (&((base+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); lua_Integer i1; lua_Integer i2; if ((((((v1))->tt_) == (((3) | ((0) << 4)))) ? (*(&i1) = (((v1)->value_).i), 1) : luaV_tointegerns(v1,&i1,F2Ieq)) && (((((v2))->tt_) == (((3) | ((0) << 4)))) ? (*(&i2) = (((v2)->value_).i), 1) : luaV_tointegerns(v2,&i2,F2Ieq))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(luaV_shiftl(i1,-(i2))); ((io)->tt_=(((3) | ((0) << 4)))); }; }};
        break;
      }
      case OP_SHL: {
        { TValue *v1 = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); TValue *v2 = (&((base+((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); lua_Integer i1; lua_Integer i2; if ((((((v1))->tt_) == (((3) | ((0) << 4)))) ? (*(&i1) = (((v1)->value_).i), 1) : luaV_tointegerns(v1,&i1,F2Ieq)) && (((((v2))->tt_) == (((3) | ((0) << 4)))) ? (*(&i2) = (((v2)->value_).i), 1) : luaV_tointegerns(v2,&i2,F2Ieq))) { pc++; { TValue *io=((&(ra)->val)); ((io)->value_).i=(luaV_shiftl(i1, i2)); ((io)->tt_=(((3) | ((0) << 4)))); }; }};
        break;
      }
      case OP_MMBIN: {
        Instruction pi = *(pc - 2);
        TValue *rb = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val);
        TMS tm = (TMS)((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        StkId result = (base+(((int)((((pi)>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        ((void)0);
        (((ci->u.l.savedpc = pc), L->top = ci->top), (luaT_trybinTM(L, (&(ra)->val), rb, result, tm)), (trap = ci->u.l.trap));
        break;
      }
      case OP_MMBINI: {
        Instruction pi = *(pc - 2);
        int imm = ((((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))) - (((1<<8)-1) >> 1));
        TMS tm = (TMS)((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        int flip = ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<(1)))<<(0)))))));
        StkId result = (base+(((int)((((pi)>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        (((ci->u.l.savedpc = pc), L->top = ci->top), (luaT_trybiniTM(L, (&(ra)->val), imm, flip, result, tm)), (trap = ci->u.l.trap));
        break;
      }
      case OP_MMBINK: {
        Instruction pi = *(pc - 2);
        TValue *imm = (k+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0))))))));
        TMS tm = (TMS)((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        int flip = ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<(1)))<<(0)))))));
        StkId result = (base+(((int)((((pi)>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        (((ci->u.l.savedpc = pc), L->top = ci->top), (luaT_trybinassocTM(L, (&(ra)->val), imm, flip, result, tm)), (trap = ci->u.l.trap));
        break;
      }
      case OP_UNM: {
        TValue *rb = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val);
        lua_Number nb;
        if (((((rb))->tt_) == (((3) | ((0) << 4))))) {
          lua_Integer ib = (((rb)->value_).i);
          { TValue *io=((&(ra)->val)); ((io)->value_).i=(((lua_Integer)(((lua_Unsigned)(0)) - ((lua_Unsigned)(ib))))); ((io)->tt_=(((3) | ((0) << 4)))); };
        }
        else if ((((((rb))->tt_) == (((3) | ((1) << 4)))) ? ((nb) = (((rb)->value_).n), 1) : (((((rb))->tt_) == (((3) | ((0) << 4)))) ? ((nb) = ((lua_Number)(((((rb)->value_).i)))), 1) : 0))) {
          { TValue *io=((&(ra)->val)); ((io)->value_).n=((-(nb))); ((io)->tt_=(((3) | ((1) << 4)))); };
        }
        else
          (((ci->u.l.savedpc = pc), L->top = ci->top), (luaT_trybinTM(L, rb, rb, ra, TM_UNM)), (trap = ci->u.l.trap));
        break;
      }
      case OP_BNOT: {
        TValue *rb = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val);
        lua_Integer ib;
        if ((((((rb))->tt_) == (((3) | ((0) << 4)))) ? (*(&ib) = (((rb)->value_).i), 1) : luaV_tointegerns(rb,&ib,F2Ieq))) {
          { TValue *io=((&(ra)->val)); ((io)->value_).i=(((lua_Integer)(((lua_Unsigned)(~((lua_Unsigned)(0)))) ^ ((lua_Unsigned)(ib))))); ((io)->tt_=(((3) | ((0) << 4)))); };
        }
        else
          (((ci->u.l.savedpc = pc), L->top = ci->top), (luaT_trybinTM(L, rb, rb, ra, TM_BNOT)), (trap = ci->u.l.trap));
        break;
      }
      case OP_NOT: {
        TValue *rb = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val);
        if ((((((rb))->tt_) == (((1) | ((0) << 4)))) || (((((((rb))->tt_)) & 0x0F)) == (0))))
          (((&(ra)->val))->tt_=(((1) | ((1) << 4))));
        else
          (((&(ra)->val))->tt_=(((1) | ((0) << 4))));
        break;
      }
      case OP_LEN: {
        (((ci->u.l.savedpc = pc), L->top = ci->top), (luaV_objlen(L, ra, (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val))), (trap = ci->u.l.trap));
        break;
      }
      case OP_CONCAT: {
        int n = ((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        L->top = ra + n;
        ((ci->u.l.savedpc = pc), (luaV_concat(L, n)), (trap = ci->u.l.trap));
        { { if ((L->l_G)->GCdebt > 0) { ((ci->u.l.savedpc = pc), L->top = (L->top)); luaC_step(L); (trap = ci->u.l.trap);}; ((void)0); }; {((void) 0); ((void) 0);}; };
        break;
      }
      case OP_CLOSE: {
        (((ci->u.l.savedpc = pc), L->top = ci->top), (luaF_close(L, ra, 0)), (trap = ci->u.l.trap));
        break;
      }
      case OP_TBC: {

        (((ci->u.l.savedpc = pc), L->top = ci->top), (luaF_newtbcupval(L, ra)));
        break;
      }
      case OP_JMP: {
        { pc += ((((int)((((i)>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0)))))) - (((1 << ((8 + 8 + 1) + 8)) - 1) >> 1)) + 0; (trap = ci->u.l.trap); };
        break;
      }
      case OP_EQ: {
        int cond;
        TValue *rb = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val);
        (((ci->u.l.savedpc = pc), L->top = ci->top), (cond = luaV_equalobj(L, (&(ra)->val), rb)), (trap = ci->u.l.trap));
        if (cond != ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<(1)))<<(0)))))))) pc++; else { Instruction ni = *pc; { pc += ((((int)((((ni)>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0)))))) - (((1 << ((8 + 8 + 1) + 8)) - 1) >> 1)) + 1; (trap = ci->u.l.trap); }; };;
        break;
      }
      case OP_LT: {
        { int cond; TValue *rb = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); if ((((((&(ra)->val)))->tt_) == (((3) | ((0) << 4)))) && ((((rb))->tt_) == (((3) | ((0) << 4))))) { lua_Integer ia = ((((&(ra)->val))->value_).i); lua_Integer ib = (((rb)->value_).i); cond = (ia < ib); } else if (((((((((&(ra)->val)))->tt_)) & 0x0F)) == (3)) && (((((((rb))->tt_)) & 0x0F)) == (3))) cond = LTnum((&(ra)->val), rb); else (((ci->u.l.savedpc = pc), L->top = ci->top), (cond = lessthanothers(L, (&(ra)->val), rb)), (trap = ci->u.l.trap)); if (cond != ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<(1)))<<(0)))))))) pc++; else { Instruction ni = *pc; { pc += ((((int)((((ni)>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0)))))) - (((1 << ((8 + 8 + 1) + 8)) - 1) >> 1)) + 1; (trap = ci->u.l.trap); }; };; };
        break;
      }
      case OP_LE: {
        { int cond; TValue *rb = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val); if ((((((&(ra)->val)))->tt_) == (((3) | ((0) << 4)))) && ((((rb))->tt_) == (((3) | ((0) << 4))))) { lua_Integer ia = ((((&(ra)->val))->value_).i); lua_Integer ib = (((rb)->value_).i); cond = (ia <= ib); } else if (((((((((&(ra)->val)))->tt_)) & 0x0F)) == (3)) && (((((((rb))->tt_)) & 0x0F)) == (3))) cond = LEnum((&(ra)->val), rb); else (((ci->u.l.savedpc = pc), L->top = ci->top), (cond = lessequalothers(L, (&(ra)->val), rb)), (trap = ci->u.l.trap)); if (cond != ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<(1)))<<(0)))))))) pc++; else { Instruction ni = *pc; { pc += ((((int)((((ni)>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0)))))) - (((1 << ((8 + 8 + 1) + 8)) - 1) >> 1)) + 1; (trap = ci->u.l.trap); }; };; };
        break;
      }
      case OP_EQK: {
        TValue *rb = (k+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0))))))));

        int cond = luaV_equalobj(((void*)0),(&(ra)->val),rb);
        if (cond != ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<(1)))<<(0)))))))) pc++; else { Instruction ni = *pc; { pc += ((((int)((((ni)>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0)))))) - (((1 << ((8 + 8 + 1) + 8)) - 1) >> 1)) + 1; (trap = ci->u.l.trap); }; };;
        break;
      }
      case OP_EQI: {
        int cond;
        int im = ((((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))) - (((1<<8)-1) >> 1));
        if ((((((&(ra)->val)))->tt_) == (((3) | ((0) << 4)))))
          cond = (((((&(ra)->val))->value_).i) == im);
        else if ((((((&(ra)->val)))->tt_) == (((3) | ((1) << 4)))))
          cond = ((((((&(ra)->val))->value_).n))==(((lua_Number)((im)))));
        else
          cond = 0;
        if (cond != ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<(1)))<<(0)))))))) pc++; else { Instruction ni = *pc; { pc += ((((int)((((ni)>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0)))))) - (((1 << ((8 + 8 + 1) + 8)) - 1) >> 1)) + 1; (trap = ci->u.l.trap); }; };;
        break;
      }
      case OP_LTI: {
        { int cond; int im = ((((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))) - (((1<<8)-1) >> 1)); if ((((((&(ra)->val)))->tt_) == (((3) | ((0) << 4))))) cond = (((((&(ra)->val))->value_).i) < im); else if ((((((&(ra)->val)))->tt_) == (((3) | ((1) << 4))))) { lua_Number fa = ((((&(ra)->val))->value_).n); lua_Number fim = ((lua_Number)((im))); cond = ((fa)<(fim)); } else { int isf = ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))); (((ci->u.l.savedpc = pc), L->top = ci->top), (cond = luaT_callorderiTM(L, (&(ra)->val), im, 0, isf, TM_LT)), (trap = ci->u.l.trap)); } if (cond != ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<(1)))<<(0)))))))) pc++; else { Instruction ni = *pc; { pc += ((((int)((((ni)>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0)))))) - (((1 << ((8 + 8 + 1) + 8)) - 1) >> 1)) + 1; (trap = ci->u.l.trap); }; };; };
        break;
      }
      case OP_LEI: {
        { int cond; int im = ((((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))) - (((1<<8)-1) >> 1)); if ((((((&(ra)->val)))->tt_) == (((3) | ((0) << 4))))) cond = (((((&(ra)->val))->value_).i) <= im); else if ((((((&(ra)->val)))->tt_) == (((3) | ((1) << 4))))) { lua_Number fa = ((((&(ra)->val))->value_).n); lua_Number fim = ((lua_Number)((im))); cond = ((fa)<=(fim)); } else { int isf = ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))); (((ci->u.l.savedpc = pc), L->top = ci->top), (cond = luaT_callorderiTM(L, (&(ra)->val), im, 0, isf, TM_LE)), (trap = ci->u.l.trap)); } if (cond != ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<(1)))<<(0)))))))) pc++; else { Instruction ni = *pc; { pc += ((((int)((((ni)>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0)))))) - (((1 << ((8 + 8 + 1) + 8)) - 1) >> 1)) + 1; (trap = ci->u.l.trap); }; };; };
        break;
      }
      case OP_GTI: {
        { int cond; int im = ((((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))) - (((1<<8)-1) >> 1)); if ((((((&(ra)->val)))->tt_) == (((3) | ((0) << 4))))) cond = (((((&(ra)->val))->value_).i) > im); else if ((((((&(ra)->val)))->tt_) == (((3) | ((1) << 4))))) { lua_Number fa = ((((&(ra)->val))->value_).n); lua_Number fim = ((lua_Number)((im))); cond = ((fa)>(fim)); } else { int isf = ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))); (((ci->u.l.savedpc = pc), L->top = ci->top), (cond = luaT_callorderiTM(L, (&(ra)->val), im, 1, isf, TM_LT)), (trap = ci->u.l.trap)); } if (cond != ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<(1)))<<(0)))))))) pc++; else { Instruction ni = *pc; { pc += ((((int)((((ni)>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0)))))) - (((1 << ((8 + 8 + 1) + 8)) - 1) >> 1)) + 1; (trap = ci->u.l.trap); }; };; };
        break;
      }
      case OP_GEI: {
        { int cond; int im = ((((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))) - (((1<<8)-1) >> 1)); if ((((((&(ra)->val)))->tt_) == (((3) | ((0) << 4))))) cond = (((((&(ra)->val))->value_).i) >= im); else if ((((((&(ra)->val)))->tt_) == (((3) | ((1) << 4))))) { lua_Number fa = ((((&(ra)->val))->value_).n); lua_Number fim = ((lua_Number)((im))); cond = ((fa)>=(fim)); } else { int isf = ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))); (((ci->u.l.savedpc = pc), L->top = ci->top), (cond = luaT_callorderiTM(L, (&(ra)->val), im, 1, isf, TM_LE)), (trap = ci->u.l.trap)); } if (cond != ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<(1)))<<(0)))))))) pc++; else { Instruction ni = *pc; { pc += ((((int)((((ni)>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0)))))) - (((1 << ((8 + 8 + 1) + 8)) - 1) >> 1)) + 1; (trap = ci->u.l.trap); }; };; };
        break;
      }
      case OP_TEST: {
        int cond = !((((((&(ra)->val)))->tt_) == (((1) | ((0) << 4)))) || ((((((((&(ra)->val)))->tt_)) & 0x0F)) == (0)));
        if (cond != ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<(1)))<<(0)))))))) pc++; else { Instruction ni = *pc; { pc += ((((int)((((ni)>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0)))))) - (((1 << ((8 + 8 + 1) + 8)) - 1) >> 1)) + 1; (trap = ci->u.l.trap); }; };;
        break;
      }
      case OP_TESTSET: {
        TValue *rb = (&((base+((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))))->val);
        if ((((((rb))->tt_) == (((1) | ((0) << 4)))) || (((((((rb))->tt_)) & 0x0F)) == (0))) == ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<(1)))<<(0))))))))
          pc++;
        else {
          { TValue *io1=((&(ra)->val)); const TValue *io2=(rb); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
          { Instruction ni = *pc; { pc += ((((int)((((ni)>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0)))))) - (((1 << ((8 + 8 + 1) + 8)) - 1) >> 1)) + 1; (trap = ci->u.l.trap); }; };
        }
        break;
      }
      case OP_CALL: {
        CallInfo *newci;
        int b = ((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        int nresults = ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))) - 1;
        if (b != 0)
          L->top = ra + b;

        (ci->u.l.savedpc = pc);
        if ((newci = luaD_precall(L, ra, nresults)) == ((void*)0))
          (trap = ci->u.l.trap);
        else {
          ci = newci;
          ci->callstatus = 0;
          goto execute;
        }
        break;
      }
      case OP_TAILCALL: {
        int b = ((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        int nparams1 = ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));

        int delta = (nparams1) ? ci->u.l.nextraargs + nparams1 : 0;
        if (b != 0)
          L->top = ra + b;
        else
          b = ((int)((L->top - ra)));
        (ci->u.l.savedpc = pc);
        if (((((int)((((i) & (1u << ((0 + 7) + 8))))))))) {



          luaF_close(L, base, (-1));
          ((void)0);
        }
        while (!(((((((&(ra)->val))->tt_)) & 0x0F)) == (6))) {
          luaD_tryfuncTM(L, ra);
          b++;
          if (L->stack_last - L->top <= (1)) { ptrdiff_t t__ = ((char *)(ra) - (char *)L->stack); { if ((L->l_G)->GCdebt > 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); }; luaD_growstack(L, 1, 1); ra = ((StkId)((char *)L->stack + (t__))); } else { ((void)0); };
        }
        if (!(((((&(ra)->val)))->tt_) == (((((6) | ((0) << 4))) | (1 << 6))))) {
          luaD_precall(L, ra, (-1));
          (trap = ci->u.l.trap);
          { if (trap) { (base = ci->func + 1); ra = (base+(((int)((((i)>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0))))))); } };
          ci->func -= delta;
          luaD_poscall(L, ci, ((int)((L->top - ra))));
          goto ret;
        }
        ci->func -= delta;
        luaD_pretailcall(L, ci, ra, b);
        goto execute;
      }
      case OP_RETURN: {
        int n = ((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0))))))) - 1;
        int nparams1 = ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        if (n < 0)
          n = ((int)((L->top - ra)));
        (ci->u.l.savedpc = pc);
        if (((((int)((((i) & (1u << ((0 + 7) + 8))))))))) {
          if (L->top < ci->top)
            L->top = ci->top;
          luaF_close(L, base, 0);
          (trap = ci->u.l.trap);
          { if (trap) { (base = ci->func + 1); ra = (base+(((int)((((i)>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0))))))); } };
        }
        if (nparams1)
          ci->func -= ci->u.l.nextraargs + nparams1;
        L->top = ra + n;
        luaD_poscall(L, ci, n);
        goto ret;
      }
      case OP_RETURN0: {
        if (L->hookmask) {
          L->top = ra;
          ((ci->u.l.savedpc = pc), (luaD_poscall(L, ci, 0)));
        }
        else {
          int nres = ci->nresults;
          L->ci = ci->previous;
          L->top = base - 1;
          while (nres-- > 0)
            (((&(L->top++)->val))->tt_=(((0) | ((0) << 4))));
        }
        goto ret;
      }
      case OP_RETURN1: {
        if (L->hookmask) {
          L->top = ra + 1;
          ((ci->u.l.savedpc = pc), (luaD_poscall(L, ci, 1)));
        }
        else {
          int nres = ci->nresults;
          L->ci = ci->previous;
          if (nres == 0)
            L->top = base - 1;
          else {
            { TValue *io1=((&(base - 1)->val)); const TValue *io2=((&(ra)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
            L->top = base;
            while (--nres > 0)
              (((&(L->top++)->val))->tt_=(((0) | ((0) << 4))));
          }
        }
       ret:
        if (ci->callstatus & (1<<2))
          return;
        else {
          ci = ci->previous;
          goto execute;
        }
      }
      case OP_FORLOOP: {
        if ((((((&(ra + 2)->val)))->tt_) == (((3) | ((0) << 4))))) {
          lua_Unsigned count = ((lua_Unsigned)(((((&(ra + 1)->val))->value_).i)));
          if (count > 0) {
            lua_Integer step = ((((&(ra + 2)->val))->value_).i);
            lua_Integer idx = ((((&(ra)->val))->value_).i);
            { TValue *io=((&(ra + 1)->val)); ((void)0); ((io)->value_).i=(count - 1); };
            idx = ((lua_Integer)(((lua_Unsigned)(idx)) + ((lua_Unsigned)(step))));
            { TValue *io=((&(ra)->val)); ((void)0); ((io)->value_).i=(idx); };
            { TValue *io=((&(ra + 3)->val)); ((io)->value_).i=(idx); ((io)->tt_=(((3) | ((0) << 4)))); };
            pc -= ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<((8 + 8 + 1))))<<(0)))))));
          }
        }
        else if (floatforloop(ra))
          pc -= ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<((8 + 8 + 1))))<<(0)))))));
        (trap = ci->u.l.trap);
        break;
      }
      case OP_FORPREP: {
        ((ci->u.l.savedpc = pc), L->top = ci->top);
        if (forprep(L, ra))
          pc += ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<((8 + 8 + 1))))<<(0))))))) + 1;
        break;
      }
      case OP_TFORPREP: {

        (((ci->u.l.savedpc = pc), L->top = ci->top), (luaF_newtbcupval(L, ra + 3)));
        pc += ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<((8 + 8 + 1))))<<(0)))))));
        i = *(pc++);
        ((void)0);
        goto l_tforcall;
      }
      case OP_TFORCALL: {
       l_tforcall:






        memcpy(ra + 4, ra, 3 * sizeof(*ra));
        L->top = ra + 4 + 3;
        ((ci->u.l.savedpc = pc), (luaD_call(L, ra + 4, ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))))), (trap = ci->u.l.trap));
        { if (trap) { (base = ci->func + 1); ra = (base+(((int)((((i)>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0))))))); } };
        i = *(pc++);
        ((void)0);
        goto l_tforloop;
      }
      case OP_TFORLOOP: {
        l_tforloop:
        if (!((((((((&(ra + 4)->val)))->tt_)) & 0x0F)) == (0))) {
          { TValue *io1=((&(ra + 2)->val)); const TValue *io2=((&(ra + 4)->val)); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
          pc -= ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<((8 + 8 + 1))))<<(0)))))));
        }
        break;
      }
      case OP_SETLIST: {
        int n = ((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        unsigned int last = ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        Table *h = ((&((((union GCUnion *)(((((&(ra)->val))->value_).gc))))->h)));
        if (n == 0)
          n = ((int)((L->top - ra))) - 1;
        else
          L->top = ci->top;
        last += n;
        if (((((int)((((i) & (1u << ((0 + 7) + 8))))))))) {
          last += ((((int)((((*pc)>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0))))))) * (((1<<8)-1) + 1);
          pc++;
        }
        if (last > luaH_realasize(h))
          luaH_resizearray(L, h, last);
        for (; n > 0; n--) {
          TValue *val = (&(ra + n)->val);
          { TValue *io1=(&h->array[last - 1]); const TValue *io2=(val); io1->value_ = io2->value_; ((io1)->tt_=(io2->tt_)); ((void)L, ((void)0)); ((void)0); };
          last--;
          ( ((((val)->tt_) & (1 << 6)) && ((((&(((union GCUnion *)((h)))->gc)))->marked) & ((1<<(5)))) && ((((((val)->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrierback_(L,(&(((union GCUnion *)((h)))->gc))) : ((void)((0))));
        }
        break;
      }
      case OP_CLOSURE: {
        Proto *p = cl->p->p[((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<((8 + 8 + 1))))<<(0)))))))];
        (((ci->u.l.savedpc = pc), L->top = ci->top), (pushclosure(L, p, cl->upvals, base, ra)));
        { { if ((L->l_G)->GCdebt > 0) { ((ci->u.l.savedpc = pc), L->top = (ra + 1)); luaC_step(L); (trap = ci->u.l.trap);}; ((void)0); }; {((void) 0); ((void) 0);}; };
        break;
      }
      case OP_VARARG: {
        int n = ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0))))))) - 1;
        (((ci->u.l.savedpc = pc), L->top = ci->top), (luaT_getvarargs(L, ci, ra, n)), (trap = ci->u.l.trap));
        break;
      }
      case OP_VARARGPREP: {
        ((ci->u.l.savedpc = pc), (luaT_adjustvarargs(L, (((int)((((i)>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0)))))), ci, cl->p)), (trap = ci->u.l.trap));
        if (trap) {
          luaD_hookcall(L, ci);
          L->oldpc = 1;
        }
        (base = ci->func + 1);
        break;
      }
      case OP_EXTRAARG: {
        ((void)0);
        break;
      }
    }
  }
}

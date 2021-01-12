
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



extern void rkname(const Proto *, int, Instruction, const char **);
extern const char * upvalname(const Proto *, int);
extern const char * gxf(const Proto *, int, Instruction, int);
extern void kname(const Proto *, int, const char **);
extern const char * gxf(const Proto *, int, Instruction, int);
extern void rname(const Proto *, int, int, const char **);
extern const char * gxf(const Proto *, int, Instruction, int);
extern void kname(const Proto *, int, const char **);
extern int findsetreg(const Proto *, int, int);
extern const char * luaF_getlocalname(const Proto *, int, int);

static const char *getobjname (const Proto *p, int lastpc, int reg,
                               const char **name) {
  int pc;
  *name = luaF_getlocalname(p, reg + 1, lastpc);
  if (*name)
    return "local";

  pc = findsetreg(p, lastpc, reg);
  if (pc != -1) {
    Instruction i = p->code[pc];
    OpCode op = (((OpCode)(((i)>>0) & ((~((~(Instruction)0)<<(7)))<<(0)))));
    switch (op) {
      case OP_MOVE: {
        int b = ((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        if (b < (((int)((((i)>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))
          return getobjname(p, pc, b, name);
        break;
      }
      case OP_GETTABUP: {
        int k = ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        kname(p, k, name);
        return gxf(p, pc, i, 1);
      }
      case OP_GETTABLE: {
        int k = ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        rname(p, pc, k, name);
        return gxf(p, pc, i, 0);
      }
      case OP_GETI: {
        *name = "integer index";
        return "field";
      }
      case OP_GETFIELD: {
        int k = ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        kname(p, k, name);
        return gxf(p, pc, i, 0);
      }
      case OP_GETUPVAL: {
        *name = upvalname(p, ((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0))))))));
        return "upvalue";
      }
      case OP_LOADK:
      case OP_LOADKX: {
        int b = (op == OP_LOADK) ? ((((int)((((i)>>(((0 + 7) + 8))) & ((~((~(Instruction)0)<<((8 + 8 + 1))))<<(0)))))))
                                 : ((((int)((((p->code[pc + 1])>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0)))))));
        if ((((((((&p->k[b]))->tt_)) & 0x0F)) == (4))) {
          *name = ((((&((((union GCUnion *)((((&p->k[b])->value_).gc))))->ts))))->contents);
          return "constant";
        }
        break;
      }
      case OP_SELF: {
        rkname(p, pc, i, name);
        return "method";
      }
      default: break;
    }
  }
  return ((void*)0);
}

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



extern int filterpc(int, int);

static int findsetreg (const Proto *p, int lastpc, int reg) {
  int pc;
  int setreg = -1;
  int jmptarget = 0;
  if ((luaP_opmodes[(((OpCode)(((p->code[lastpc])>>0) & ((~((~(Instruction)0)<<(7)))<<(0)))))] & (1 << 7)))
    lastpc--;
  for (pc = 0; pc < lastpc; pc++) {
    Instruction i = p->code[pc];
    OpCode op = (((OpCode)(((i)>>0) & ((~((~(Instruction)0)<<(7)))<<(0)))));
    int a = (((int)((((i)>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0))))));
    int change;
    switch (op) {
      case OP_LOADNIL: {
        int b = ((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
        change = (a <= reg && reg <= a + b);
        break;
      }
      case OP_TFORCALL: {
        change = (reg >= a + 2);
        break;
      }
      case OP_CALL:
      case OP_TAILCALL: {
        change = (reg >= a);
        break;
      }
      case OP_JMP: {
        int b = ((((int)((((i)>>((0 + 7))) & ((~((~(Instruction)0)<<(((8 + 8 + 1) + 8))))<<(0)))))) - (((1 << ((8 + 8 + 1) + 8)) - 1) >> 1));
        int dest = pc + 1 + b;

        if (dest <= lastpc && dest > jmptarget)
          jmptarget = dest;
        change = 0;
        break;
      }
      default:
        change = ((luaP_opmodes[op] & (1 << 3)) && reg == a);
        break;
    }
    if (change)
      setreg = filterpc(pc, jmptarget);
  }
  return setreg;
}

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



extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern void luaK_int(FuncState *, int, lua_Integer);
extern void luaK_float(FuncState *, int, lua_Number);
extern int luaK_codek(FuncState *, int, int);
extern void str2K(FuncState *, expdesc *);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern void luaK_nil(FuncState *, int, int);
extern void luaK_dischargevars(FuncState *, expdesc *);

extern void discharge2reg (FuncState *fs, expdesc *e, int reg) {
  luaK_dischargevars(fs, e);
  switch (e->k) {
    case VNIL: {
      luaK_nil(fs, reg, 1);
      break;
    }
    case VFALSE: {
      luaK_codeABCk(fs,OP_LOADFALSE,reg,0,0,0);
      break;
    }
    case VTRUE: {
      luaK_codeABCk(fs,OP_LOADTRUE,reg,0,0,0);
      break;
    }
    case VKSTR: {
      str2K(fs, e);
    }
    case VK: {
      luaK_codek(fs, reg, e->u.info);
      break;
    }
    case VKFLT: {
      luaK_float(fs, reg, e->u.nval);
      break;
    }
    case VKINT: {
      luaK_int(fs, reg, e->u.ival);
      break;
    }
    case VRELOC: {
      Instruction *pc = &((fs)->f->code[(e)->u.info]);
      ((*pc) = (((*pc)&(~((~((~(Instruction)0)<<(8)))<<((0 + 7))))) | ((((Instruction)(reg))<<(0 + 7))&((~((~(Instruction)0)<<(8)))<<((0 + 7))))));
      break;
    }
    case VNONRELOC: {
      if (reg != e->u.info)
        luaK_codeABCk(fs,OP_MOVE,reg,e->u.info,0,0);
      break;
    }
    default: {
      ((void)0);
      return;
    }
  }
  e->u.info = reg;
  e->k = VNONRELOC;
}
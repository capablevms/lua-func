
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



extern const char * getobjname(const Proto *, int, int, const char **);
extern int currentpc(CallInfo *);

static const char *funcnamefromcode (lua_State *L, CallInfo *ci,
                                     const char **name) {
  TMS tm = (TMS)0;
  const Proto *p = (((&((((union GCUnion *)(((((&((ci)->func)->val))->value_).gc))))->cl.l))))->p;
  int pc = currentpc(ci);
  Instruction i = p->code[pc];
  if (ci->callstatus & (1<<3)) {
    *name = "?";
    return "hook";
  }
  switch ((((OpCode)(((i)>>0) & ((~((~(Instruction)0)<<(7)))<<(0)))))) {
    case OP_CALL:
    case OP_TAILCALL:
      return getobjname(p, pc, (((int)((((i)>>((0 + 7))) & ((~((~(Instruction)0)<<(8)))<<(0)))))), name);
    case OP_TFORCALL: {
      *name = "for iterator";
       return "for iterator";
    }

    case OP_SELF: case OP_GETTABUP: case OP_GETTABLE:
    case OP_GETI: case OP_GETFIELD:
      tm = TM_INDEX;
      break;
    case OP_SETTABUP: case OP_SETTABLE: case OP_SETI: case OP_SETFIELD:
      tm = TM_NEWINDEX;
      break;
    case OP_MMBIN: case OP_MMBINI: case OP_MMBINK: {
      tm = ((TMS)(((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))));
      break;
    }
    case OP_UNM: tm = TM_UNM; break;
    case OP_BNOT: tm = TM_BNOT; break;
    case OP_LEN: tm = TM_LEN; break;
    case OP_CONCAT: tm = TM_CONCAT; break;
    case OP_EQ: tm = TM_EQ; break;
    case OP_LT: case OP_LE: case OP_LTI: case OP_LEI:
      *name = "order";
      return "metamethod";
    case OP_CLOSE: case OP_RETURN:
      *name = "close";
      return "metamethod";
    default:
      return ((void*)0);
  }
  *name = (((L->l_G)->tmname[tm])->contents) + 2;
  return "metamethod";
}
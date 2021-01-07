
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



extern void luaK_setoneret(FuncState *, expdesc *);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern void freeregs(FuncState *, int, int);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern void freereg(FuncState *, int);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern void freereg(FuncState *, int);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern int luaK_codeABCk(FuncState *, OpCode, int, int, int, int);
extern void const2exp(TValue *, expdesc *);
extern TValue * const2val(FuncState *, const expdesc *);

void luaK_dischargevars (FuncState *fs, expdesc *e) {
  switch (e->k) {
    case VCONST: {
      const2exp(const2val(fs, e), e);
      break;
    }
    case VLOCAL: {
      e->u.info = e->u.var.sidx;
      e->k = VNONRELOC;
      break;
    }
    case VUPVAL: {
      e->u.info = luaK_codeABCk(fs,OP_GETUPVAL,0,e->u.info,0,0);
      e->k = VRELOC;
      break;
    }
    case VINDEXUP: {
      e->u.info = luaK_codeABCk(fs,OP_GETTABUP,0,e->u.ind.t,e->u.ind.idx,0);
      e->k = VRELOC;
      break;
    }
    case VINDEXI: {
      freereg(fs, e->u.ind.t);
      e->u.info = luaK_codeABCk(fs,OP_GETI,0,e->u.ind.t,e->u.ind.idx,0);
      e->k = VRELOC;
      break;
    }
    case VINDEXSTR: {
      freereg(fs, e->u.ind.t);
      e->u.info = luaK_codeABCk(fs,OP_GETFIELD,0,e->u.ind.t,e->u.ind.idx,0);
      e->k = VRELOC;
      break;
    }
    case VINDEXED: {
      freeregs(fs, e->u.ind.t, e->u.ind.idx);
      e->u.info = luaK_codeABCk(fs,OP_GETTABLE,0,e->u.ind.t,e->u.ind.idx,0);
      e->k = VRELOC;
      break;
    }
    case VVARARG: case VCALL: {
      luaK_setoneret(fs, e);
      break;
    }
    default: break;
  }
}
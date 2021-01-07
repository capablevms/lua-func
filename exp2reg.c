
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



extern void patchlistaux(FuncState *, int, int, int, int);
extern void patchlistaux(FuncState *, int, int, int, int);
extern int luaK_getlabel(FuncState *);
extern void luaK_patchtohere(FuncState *, int);
extern int code_loadbool(FuncState *, int, OpCode);
extern int code_loadbool(FuncState *, int, OpCode);
extern int luaK_jump(FuncState *);
extern int need_value(FuncState *, int);
extern int need_value(FuncState *, int);
extern void luaK_concat(FuncState *, int *, int);
extern void discharge2reg(FuncState *, expdesc *, int);

static void exp2reg (FuncState *fs, expdesc *e, int reg) {
  discharge2reg(fs, e, reg);
  if (e->k == VJMP)
    luaK_concat(fs, &e->t, e->u.info);
  if (((e)->t != (e)->f)) {
    int final;
    int p_f = (-1);
    int p_t = (-1);
    if (need_value(fs, e->t) || need_value(fs, e->f)) {
      int fj = (e->k == VJMP) ? (-1) : luaK_jump(fs);
      p_f = code_loadbool(fs, reg, OP_LFALSESKIP);
      p_t = code_loadbool(fs, reg, OP_LOADTRUE);

      luaK_patchtohere(fs, fj);
    }
    final = luaK_getlabel(fs);
    patchlistaux(fs, e->f, final, reg, p_f);
    patchlistaux(fs, e->t, final, reg, p_t);
  }
  e->f = e->t = (-1);
  e->u.info = reg;
  e->k = VNONRELOC;
}

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

extern const struct {
  lu_byte left;
  lu_byte right;
} priority[];

extern void luaK_posfix(FuncState *, BinOpr, expdesc *, expdesc *, int);
extern void luaK_infix(FuncState *, BinOpr, expdesc *);
extern void luaX_next(LexState *);
extern BinOpr getbinopr(int);
extern void simpleexp(LexState *, expdesc *);
extern void luaK_prefix(FuncState *, UnOpr, expdesc *, int);
extern UnOpr getunopr(int);
extern void luaE_incCstack(lua_State *);

static BinOpr subexpr (LexState *ls, expdesc *v, int limit) {
  BinOpr op;
  UnOpr uop;
  luaE_incCstack(ls->L);
  uop = getunopr(ls->t.token);
  if (uop != OPR_NOUNOPR) {
    int line = ls->linenumber;
    luaX_next(ls);
    subexpr(ls, v, 12);
    luaK_prefix(ls->fs, uop, v, line);
  }
  else simpleexp(ls, v);

  op = getbinopr(ls->t.token);
  while (op != OPR_NOBINOPR && priority[op].left > limit) {
    expdesc v2;
    BinOpr nextop;
    int line = ls->linenumber;
    luaX_next(ls);
    luaK_infix(ls->fs, op, v);

    nextop = subexpr(ls, &v2, priority[op].right);
    luaK_posfix(ls->fs, op, v, &v2, line);
    op = nextop;
  }
  ((ls)->L->nCcalls--);
  return op;
}
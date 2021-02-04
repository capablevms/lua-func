
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



extern void codenot(FuncState *, expdesc *);
extern void codeunexpval(FuncState *, OpCode, expdesc *, int);
extern int constfolding(FuncState *, int, expdesc *, const expdesc *);
extern void luaK_dischargevars(FuncState *, expdesc *);

void luaK_prefix (FuncState *fs, UnOpr op, expdesc *e, int line) {
  static const expdesc ef = {VKINT, {0}, (-1), (-1)};
  luaK_dischargevars(fs, e);
  switch (op) {
    case OPR_MINUS: case OPR_BNOT:
      if (constfolding(fs, op + 12, e, &ef))
        break;

    case OPR_LEN:
      codeunexpval(fs, ((OpCode)(op + OP_UNM)), e, line);
      break;
    case OPR_NOT: codenot(fs, e); break;
    default: ((void)0);
  }
}
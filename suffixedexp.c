
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



extern void funcargs(LexState *, expdesc *, int);
extern void luaK_exp2nextreg(FuncState *, expdesc *);
extern void funcargs(LexState *, expdesc *, int);
extern void luaK_self(FuncState *, expdesc *, expdesc *);
extern void codename(LexState *, expdesc *);
extern void luaX_next(LexState *);
extern void luaK_indexed(FuncState *, expdesc *, expdesc *);
extern void yindex(LexState *, expdesc *);
extern void luaK_exp2anyregup(FuncState *, expdesc *);
extern void fieldsel(LexState *, expdesc *);
extern void primaryexp(LexState *, expdesc *);

static void suffixedexp (LexState *ls, expdesc *v) {


  FuncState *fs = ls->fs;
  int line = ls->linenumber;
  primaryexp(ls, v);
  for (;;) {
    switch (ls->t.token) {
      case '.': {
        fieldsel(ls, v);
        break;
      }
      case '[': {
        expdesc key;
        luaK_exp2anyregup(fs, v);
        yindex(ls, &key);
        luaK_indexed(fs, v, &key);
        break;
      }
      case ':': {
        expdesc key;
        luaX_next(ls);
        codename(ls, &key);
        luaK_self(fs, v, &key);
        funcargs(ls, v, line);
        break;
      }
      case '(': case TK_STRING: case '{': {
        luaK_exp2nextreg(fs, v);
        funcargs(ls, v, line);
        break;
      }
      default: return;
    }
  }
}
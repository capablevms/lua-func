
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



extern void luaK_indexed(FuncState *, expdesc *, expdesc *);
extern void codename(LexState *, expdesc *);
extern void luaX_next(LexState *);
extern void luaK_exp2anyregup(FuncState *, expdesc *);

static void fieldsel (LexState *ls, expdesc *v) {

  FuncState *fs = ls->fs;
  expdesc key;
  luaK_exp2anyregup(fs, v);
  luaX_next(ls);
  codename(ls, &key);
  luaK_indexed(fs, v, &key);
}

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



extern void lexerror(LexState *, const char *, int);
extern int luaZ_fill(ZIO *);
extern int luaZ_fill(ZIO *);

static void inclinenumber (LexState *ls) {
  int old = ls->current;
  ((void)0);
  (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z)));
  if ((ls->current == '\n' || ls->current == '\r') && ls->current != old)
    (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z)));
  if (++ls->linenumber >= 2147483647)
    lexerror(ls, "chunk has too many lines", 0);
}
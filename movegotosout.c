
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

typedef struct BlockCnt {
  struct BlockCnt *previous;
  int firstlabel;
  int firstgoto;
  lu_byte nactvar;
  lu_byte upval;
  lu_byte isloop;
  lu_byte insidetbc;
} BlockCnt;


extern int stacklevel(FuncState *, int);
extern int stacklevel(FuncState *, int);

static void movegotosout (FuncState *fs, BlockCnt *bl) {
  int i;
  Labellist *gl = &fs->ls->dyd->gt;

  for (i = bl->firstgoto; i < gl->n; i++) {
    Labeldesc *gt = &gl->arr[i];

    if (stacklevel(fs, gt->nactvar) > stacklevel(fs, bl->nactvar))
      gt->close |= bl->upval;
    gt->nactvar = bl->nactvar;
  }
}
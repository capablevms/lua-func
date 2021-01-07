
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


extern void init_exp(expdesc *, expkind, int);
extern int newupvalue(FuncState *, TString *, expdesc *);
extern void singlevaraux(FuncState *, TString *, expdesc *, int);
extern int searchupvalue(FuncState *, TString *);
extern void markupval(FuncState *, int);
extern int searchvar(FuncState *, TString *, expdesc *);
extern void init_exp(expdesc *, expkind, int);

static void singlevaraux (FuncState *fs, TString *n, expdesc *var, int base) {
  if (fs == ((void*)0))
    init_exp(var, VVOID, 0);
  else {
    int v = searchvar(fs, n, var);
    if (v >= 0) {
      if (v == VLOCAL && !base)
        markupval(fs, var->u.var.vidx);
    }
    else {
      int idx = searchupvalue(fs, n);
      if (idx < 0) {
        singlevaraux(fs->prev, n, var, 0);
        if (var->k == VLOCAL || var->k == VUPVAL)
          idx = newupvalue(fs, n, var);
        else
          return;
      }
      init_exp(var, VUPVAL, idx);
    }
  }
}
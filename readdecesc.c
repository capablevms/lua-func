
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



extern void esccheck(LexState *, int, const char *);
extern int luaZ_fill(ZIO *);
extern void save(LexState *, int);

extern int readdecesc (LexState *ls) {
  int i;
  int r = 0;
  for (i = 0; i < 3 && (luai_ctype_[(ls->current)+1] & ((1 << (1)))); i++) {
    r = 10*r + ls->current - '0';
    (save(ls, ls->current), (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z))));
  }
  esccheck(ls, r <= (127*2 +1), "decimal escape too large");
  ((ls->buff)->n -= (i));
  return r;
}
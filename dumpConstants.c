
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

typedef struct {
  lua_State *L;
  lua_Writer writer;
  void *data;
  int strip;
  int status;
} DumpState;


extern void dumpString(DumpState *, const TString *);
extern void dumpInteger(DumpState *, lua_Integer);
extern void dumpNumber(DumpState *, lua_Number);
extern void dumpByte(DumpState *, int);
extern void dumpInt(DumpState *, int);

static void dumpConstants (DumpState *D, const Proto *f) {
  int i;
  int n = f->sizek;
  dumpInt(D, n);
  for (i = 0; i < n; i++) {
    const TValue *o = &f->k[i];
    int tt = ((((o)->tt_)) & 0x3F);
    dumpByte(D, tt);
    switch (tt) {
      case ((3) | ((1) << 4)):
        dumpNumber(D, (((o)->value_).n));
        break;
      case ((3) | ((0) << 4)):
        dumpInteger(D, (((o)->value_).i));
        break;
      case ((4) | ((0) << 4)):
      case ((4) | ((1) << 4)):
        dumpString(D, ((&((((union GCUnion *)((((o)->value_).gc))))->ts))));
        break;
      default:
        ((void)0);
    }
  }
}
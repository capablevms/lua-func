
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


extern void dumpBlock(DumpState *, const void *, size_t);
extern void dumpSize(DumpState *, size_t);
extern void dumpSize(DumpState *, size_t);

static void dumpString (DumpState *D, const TString *s) {
  if (s == ((void*)0))
    dumpSize(D, 0);
  else {
    size_t size = ((s)->tt == ((4) | ((0) << 4)) ? (s)->shrlen : (s)->u.lnglen);
    const char *str = ((s)->contents);
    dumpSize(D, size + 1);
    dumpBlock(D,str,(size)*sizeof((str)[0]));
  }
}

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

static void dumpSize (DumpState *D, size_t x) {
  lu_byte buff[((sizeof(size_t) * 8 / 7) + 1)];
  int n = 0;
  do {
    buff[((sizeof(size_t) * 8 / 7) + 1) - (++n)] = x & 0x7f;
    x >>= 7;
  } while (x != 0);
  buff[((sizeof(size_t) * 8 / 7) + 1) - 1] |= 0x80;
  dumpBlock(D,buff + ((sizeof(size_t) * 8 / 7) + 1) - n,(n)*sizeof((buff + ((sizeof(size_t) * 8 / 7) + 1) - n)[0]));
}
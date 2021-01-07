
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
  FILE *f;
  int c;
  int n;
  char buff[200 + 1];
} RN;


extern int getc(FILE *);

static int nextc (RN *rn) {
  if (rn->n >= 200) {
    rn->buff[0] = '\0';
    return 0;
  }
  else {
    rn->buff[rn->n++] = rn->c;
    rn->c = getc(rn->f);
    return 1;
  }
}

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

typedef struct LoadF {
  int n;
  FILE *f;
  char buff[8192];
} LoadF;


extern int getc(FILE *);
extern int getc(FILE *);

extern int skipBOM (LoadF *lf) {
  const char *p = "\xEF\xBB\xBF";
  int c;
  lf->n = 0;
  do {
    c = getc(lf->f);
    if (c == (-1) || c != *(const unsigned char *)p++) return c;
    lf->buff[lf->n++] = c;
  } while (*p != '\0');
  lf->n = 0;
  return getc(lf->f);
}
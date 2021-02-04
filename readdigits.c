
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


extern int nextc(RN *);
extern const unsigned short ** __ctype_b_loc();
extern const unsigned short ** __ctype_b_loc();

extern int readdigits (RN *rn, int hex) {
  int count = 0;
  while ((hex ? ((*__ctype_b_loc ())[(int) ((rn->c))] & (unsigned short int) _ISxdigit) : ((*__ctype_b_loc ())[(int) ((rn->c))] & (unsigned short int) _ISdigit)) && nextc(rn))
    count++;
  return count;
}
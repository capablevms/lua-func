
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



extern int fflush(FILE *);
extern int fprintf(FILE *restrict, const char *restrict, ...);
extern int fflush(FILE *);
extern int fprintf(FILE *restrict, const char *restrict, ...);
extern int fflush(FILE *);
extern int fprintf(FILE *restrict, const char *restrict, ...);
extern int strcmp(const char *, const char *);
extern int strcmp(const char *, const char *);

static void warnf (void *ud, const char *message, int tocont) {
  int *warnstate = (int *)ud;
  if (*warnstate != 2 && !tocont && *message == '@') {
    if (strcmp(message, "@off") == 0)
      *warnstate = 0;
    else if (strcmp(message, "@on") == 0)
      *warnstate = 1;
    return;
  }
  else if (*warnstate == 0)
    return;
  if (*warnstate == 1)
    (fprintf(stderr, ("%s"), ("Lua warning: ")), fflush(stderr));
  (fprintf(stderr, ("%s"), (message)), fflush(stderr));
  if (tocont)
    *warnstate = 2;
  else {
    (fprintf(stderr, ("%s"), ("\n")), fflush(stderr));
    *warnstate = 1;
  }
}
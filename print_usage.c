
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

extern const char *progname;

extern int fflush(FILE *);
extern int fprintf(FILE *restrict, const char *restrict, ...);
extern int fflush(FILE *);
extern int fprintf(FILE *restrict, const char *restrict, ...);
extern int fflush(FILE *);
extern int fprintf(FILE *restrict, const char *restrict, ...);
extern int fflush(FILE *);
extern int fprintf(FILE *restrict, const char *restrict, ...);

static void print_usage (const char *badoption) {
  (fprintf(stderr, ("%s: "), (progname)), fflush(stderr));
  if (badoption[1] == 'e' || badoption[1] == 'l')
    (fprintf(stderr, ("'%s' needs argument\n"), (badoption)), fflush(stderr));
  else
    (fprintf(stderr, ("unrecognized option '%s'\n"), (badoption)), fflush(stderr));
  (fprintf(stderr, ("usage: %s [options] [script [args]]\n" "Available options are:\n" "  -e stat  execute string 'stat'\n" "  -i       enter interactive mode after executing 'script'\n" "  -l name  require library 'name' into global 'name'\n" "  -v       show version information\n" "  -E       ignore environment variables\n" "  -W       turn warnings on\n" "  --       stop handling options\n" "  -        stop handling options and execute stdin\n"), (progname)), fflush(stderr));
# 82 "lua.c"
}
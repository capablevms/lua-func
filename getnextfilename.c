
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



extern char * strchr(const char *, int);

static const char *getnextfilename (char **path, char *end) {
  char *sep;
  char *name = *path;
  if (name == end)
    return ((void*)0);
  else if (*name == '\0') {
    *name = *";";
    name++;
  }
  sep = strchr(name, *";");
  if (sep == ((void*)0))
    sep = end;
  *sep = '\0';
  *path = sep;
  return name;
}
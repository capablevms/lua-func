
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



extern int strcmp(const char *, const char *);
extern const char * getobjname(const Proto *, int, int, const char **);
extern const char * upvalname(const Proto *, int);

extern const char *gxf (const Proto *p, int pc, Instruction i, int isup) {
  int t = ((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))));
  const char *name;
  if (isup)
    name = upvalname(p, t);
  else
    getobjname(p, pc, t, &name);
  return (name && strcmp(name, "_ENV") == 0) ? "global" : "field";
}
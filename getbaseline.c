
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




extern int getbaseline (const Proto *f, int pc, int *basepc) {
  if (f->sizeabslineinfo == 0 || pc < f->abslineinfo[0].pc) {
    *basepc = -1;
    return f->linedefined;
  }
  else {
    unsigned int i;
    if (pc >= f->abslineinfo[f->sizeabslineinfo - 1].pc)
      i = f->sizeabslineinfo - 1;
    else {
      unsigned int j = f->sizeabslineinfo - 1;
      i = 0;
      while (i < j - 1) {
        unsigned int m = (j + i) / 2;
        if (pc >= f->abslineinfo[m].pc)
          i = m;
        else
          j = m;
      }
    }
    *basepc = f->abslineinfo[i].pc;
    return f->abslineinfo[i].line;
  }
}
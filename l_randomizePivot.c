
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



extern void * memcpy(void *restrict, const void *restrict, size_t);
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern time_t time(time_t *);
extern clock_t clock();

extern unsigned int l_randomizePivot (void) {
  clock_t c = clock();
  time_t t = time(((void*)0));
  unsigned int buff[(sizeof(c) / sizeof(unsigned int)) + (sizeof(t) / sizeof(unsigned int))];
  unsigned int i, rnd = 0;
  memcpy(buff, &c, (sizeof(c) / sizeof(unsigned int)) * sizeof(unsigned int));
  memcpy(buff + (sizeof(c) / sizeof(unsigned int)), &t, (sizeof(t) / sizeof(unsigned int)) * sizeof(unsigned int));
  for (i = 0; i < (sizeof(buff) / sizeof(unsigned int)); i++)
    rnd += buff[i];
  return rnd;
}
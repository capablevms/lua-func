
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



extern unsigned int luaS_hash(const char *, size_t, unsigned int);
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern time_t time(time_t *);

static unsigned int luai_makeseed (lua_State *L) {
  char buff[3 * sizeof(size_t)];
  unsigned int h = ((unsigned int)((time(((void*)0)))));
  int p = 0;
  { size_t t = ((size_t)((L))); memcpy(buff + p, &t, sizeof(t)); p += sizeof(t); };
  { size_t t = ((size_t)((&h))); memcpy(buff + p, &t, sizeof(t)); p += sizeof(t); };
  { size_t t = ((size_t)((&lua_newstate))); memcpy(buff + p, &t, sizeof(t)); p += sizeof(t); };
  ((void)0);
  return luaS_hash(buff, p, h);
}
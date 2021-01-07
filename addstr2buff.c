
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

typedef struct BuffFS {
  lua_State *L;
  int pushed;
  int blen;
  char space[200];
} BuffFS;


extern void pushstr(BuffFS *, const char *, size_t);
extern void clearbuff(BuffFS *);
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern char * getbuff(BuffFS *, int);

static void addstr2buff (BuffFS *buff, const char *str, size_t slen) {
  if (slen <= 200) {
    char *bf = getbuff(buff, ((int)((slen))));
    memcpy(bf, str, slen);
    ((buff)->blen += (((int)((slen)))));
  }
  else {
    clearbuff(buff);
    pushstr(buff, str, slen);
  }
}

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



extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern void luaL_addstring(luaL_Buffer *, const char *);
extern int snprintf(char *restrict, size_t, const char *restrict, ...);
extern int snprintf(char *restrict, size_t, const char *restrict, ...);
extern const unsigned short ** __ctype_b_loc();
extern const unsigned short ** __ctype_b_loc();
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);

static void addquoted (luaL_Buffer *b, const char *s, size_t len) {
  ((void)((b)->n < (b)->size || luaL_prepbuffsize((b), 1)), ((b)->b[(b)->n++] = ('"')));
  while (len--) {
    if (*s == '"' || *s == '\\' || *s == '\n') {
      ((void)((b)->n < (b)->size || luaL_prepbuffsize((b), 1)), ((b)->b[(b)->n++] = ('\\')));
      ((void)((b)->n < (b)->size || luaL_prepbuffsize((b), 1)), ((b)->b[(b)->n++] = (*s)));
    }
    else if (((*__ctype_b_loc ())[(int) ((((unsigned char)(*s))))] & (unsigned short int) _IScntrl)) {
      char buff[10];
      if (!((*__ctype_b_loc ())[(int) ((((unsigned char)(*(s+1)))))] & (unsigned short int) _ISdigit))
        snprintf(buff,sizeof(buff),"\\%d",(int)((unsigned char)(*s)));
      else
        snprintf(buff,sizeof(buff),"\\%03d",(int)((unsigned char)(*s)));
      luaL_addstring(b, buff);
    }
    else
      ((void)((b)->n < (b)->size || luaL_prepbuffsize((b), 1)), ((b)->b[(b)->n++] = (*s)));
    s++;
  }
  ((void)((b)->n < (b)->size || luaL_prepbuffsize((b), 1)), ((b)->b[(b)->n++] = ('"')));
}
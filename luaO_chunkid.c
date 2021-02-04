
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
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern char * strchr(const char *, int);
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern void * memcpy(void *restrict, const void *restrict, size_t);

void luaO_chunkid (char *out, const char *source, size_t srclen) {
  size_t bufflen = 60;
  if (*source == '=') {
    if (srclen <= bufflen)
      memcpy(out, source + 1, srclen * sizeof(char));
    else {
      ( memcpy(out,source + 1,(bufflen - 1) * sizeof(char)), out += (bufflen - 1) );
      *out = '\0';
    }
  }
  else if (*source == '@') {
    if (srclen <= bufflen)
      memcpy(out, source + 1, srclen * sizeof(char));
    else {
      ( memcpy(out,"...",((sizeof("...")/sizeof(char) - 1)) * sizeof(char)), out += ((sizeof("...")/sizeof(char) - 1)) );
      bufflen -= (sizeof("...")/sizeof(char) - 1);
      memcpy(out, source + 1 + srclen - bufflen, bufflen * sizeof(char));
    }
  }
  else {
    const char *nl = strchr(source, '\n');
    ( memcpy(out,"[string \"",((sizeof("[string \"")/sizeof(char) - 1)) * sizeof(char)), out += ((sizeof("[string \"")/sizeof(char) - 1)) );
    bufflen -= (sizeof("[string \"" "..." "\"]")/sizeof(char) - 1) + 1;
    if (srclen < bufflen && nl == ((void*)0)) {
      ( memcpy(out,source,(srclen) * sizeof(char)), out += (srclen) );
    }
    else {
      if (nl != ((void*)0)) srclen = nl - source;
      if (srclen > bufflen) srclen = bufflen;
      ( memcpy(out,source,(srclen) * sizeof(char)), out += (srclen) );
      ( memcpy(out,"...",((sizeof("...")/sizeof(char) - 1)) * sizeof(char)), out += ((sizeof("...")/sizeof(char) - 1)) );
    }
    memcpy(out, "\"]", ((sizeof("\"]")/sizeof(char) - 1) + 1) * sizeof(char));
  }
}
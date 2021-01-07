
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



extern void luaL_addstring(luaL_Buffer *, const char *);
extern void luaL_addstring(luaL_Buffer *, const char *);
extern void luaL_addlstring(luaL_Buffer *, const char *, size_t);
extern char * strstr(const char *, const char *);
extern unsigned long strlen(const char *);

extern void luaL_addgsub (luaL_Buffer *b, const char *s,
                                     const char *p, const char *r) {
  const char *wild;
  size_t l = strlen(p);
  while ((wild = strstr(s, p)) != ((void*)0)) {
    luaL_addlstring(b, s, wild - s);
    luaL_addstring(b, r);
    s = wild + l;
  }
  luaL_addstring(b, s);
}
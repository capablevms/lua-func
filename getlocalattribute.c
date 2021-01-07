
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



extern void luaK_semerror(LexState *, const char *);
extern const char * luaO_pushfstring(lua_State *, const char *, ...);
extern int strcmp(const char *, const char *);
extern int strcmp(const char *, const char *);
extern void checknext(LexState *, int);
extern TString * str_checkname(LexState *);
extern int testnext(LexState *, int);

static int getlocalattribute (LexState *ls) {

  if (testnext(ls, '<')) {
    const char *attr = ((str_checkname(ls))->contents);
    checknext(ls, '>');
    if (strcmp(attr, "const") == 0)
      return 1;
    else if (strcmp(attr, "close") == 0)
      return 2;
    else
      luaK_semerror(ls,
        luaO_pushfstring(ls->L, "unknown attribute '%s'", attr));
  }
  return 0;
}
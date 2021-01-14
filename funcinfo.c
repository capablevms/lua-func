
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



extern void luaO_chunkid(char *, const char *, size_t);

extern void funcinfo (lua_Debug *ar, Closure *cl) {
  if (((cl) == ((void*)0) || (cl)->c.tt == ((6) | ((2) << 4)))) {
    ar->source = "=[C]";
    ar->srclen = (sizeof("=[C]")/sizeof(char) - 1);
    ar->linedefined = -1;
    ar->lastlinedefined = -1;
    ar->what = "C";
  }
  else {
    const Proto *p = cl->l.p;
    if (p->source) {
      ar->source = ((p->source)->contents);
      ar->srclen = ((p->source)->tt == ((4) | ((0) << 4)) ? (p->source)->shrlen : (p->source)->u.lnglen);
    }
    else {
      ar->source = "=?";
      ar->srclen = (sizeof("=?")/sizeof(char) - 1);
    }
    ar->linedefined = p->linedefined;
    ar->lastlinedefined = p->lastlinedefined;
    ar->what = (ar->linedefined == 0) ? "main" : "Lua";
  }
  luaO_chunkid(ar->short_src, ar->source, ar->srclen);
}

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



extern void * luaM_saferealloc_(lua_State *, void *, size_t, size_t);
extern TString * luaS_newlstr(lua_State *, const char *, size_t);

void luaX_setinput (lua_State *L, LexState *ls, ZIO *z, TString *source,
                    int firstchar) {
  ls->t.token = 0;
  ls->L = L;
  ls->current = firstchar;
  ls->lookahead.token = TK_EOS;
  ls->z = z;
  ls->fs = ((void*)0);
  ls->linenumber = 1;
  ls->lastline = 1;
  ls->source = source;
  ls->envn = (luaS_newlstr(L, "" "_ENV", (sizeof("_ENV")/sizeof(char))-1));
  ((ls->buff)->buffer = ((char *)((luaM_saferealloc_(ls->L, ((ls->buff)->buffer), ((ls->buff)->buffsize)*sizeof(char), (32)*sizeof(char))))), (ls->buff)->buffsize = 32);
}
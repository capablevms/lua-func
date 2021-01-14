
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



extern void luaX_syntaxerror(LexState *, const char *);
extern const char * luaO_pushfstring(lua_State *, const char *, ...);
extern const char * luaX_token2str(LexState *, int);
extern const char * luaX_token2str(LexState *, int);
extern void error_expected(LexState *, int);
extern long __builtin_expect(long, long);
extern int testnext(LexState *, int);

extern void check_match (LexState *ls, int what, int who, int where) {
  if ((__builtin_expect(((!testnext(ls, what)) != 0), 0))) {
    if (where == ls->linenumber)
      error_expected(ls, what);
    else {
      luaX_syntaxerror(ls, luaO_pushfstring(ls->L,
             "%s expected (to close %s at line %d)",
              luaX_token2str(ls, what), luaX_token2str(ls, who), where));
    }
  }
}
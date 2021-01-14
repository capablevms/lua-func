
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



extern const char * luaX_token2str(LexState *, int);
extern const char * luaO_pushfstring(lua_State *, const char *, ...);
extern void save(LexState *, int);

extern const char *txtToken (LexState *ls, int token) {
  switch (token) {
    case TK_NAME: case TK_STRING:
    case TK_FLT: case TK_INT:
      save(ls, '\0');
      return luaO_pushfstring(ls->L, "'%s'", ((ls->buff)->buffer));
    default:
      return luaX_token2str(ls, token);
  }
}

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

extern const char *const luaX_tokens [];

extern const char * luaO_pushfstring(lua_State *, const char *, ...);
extern const char * luaO_pushfstring(lua_State *, const char *, ...);
extern const char * luaO_pushfstring(lua_State *, const char *, ...);

const char *luaX_token2str (LexState *ls, int token) {
  if (token < ((127*2 +1) + 1)) {
    if ((luai_ctype_[(token)+1] & ((1 << (2)))))
      return luaO_pushfstring(ls->L, "'%c'", token);
    else
      return luaO_pushfstring(ls->L, "'<\\%d>'", token);
  }
  else {
    const char *s = luaX_tokens[token - ((127*2 +1) + 1)];
    if (token < TK_EOS)
      return luaO_pushfstring(ls->L, "'%s'", s);
    else
      return s;
  }
}
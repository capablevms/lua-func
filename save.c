
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
extern void lexerror(LexState *, const char *, int);

static void save (LexState *ls, int c) {
  Mbuffer *b = ls->buff;
  if (((b)->n) + 1 > ((b)->buffsize)) {
    size_t newsize;
    if (((b)->buffsize) >= (sizeof(size_t) < sizeof(lua_Integer) ? ((size_t)(~(size_t)0)) : (size_t)(9223372036854775807LL))/2)
      lexerror(ls, "lexical element too long", 0);
    newsize = ((b)->buffsize) * 2;
    ((b)->buffer = ((char *)((luaM_saferealloc_(ls->L, ((b)->buffer), ((b)->buffsize)*sizeof(char), (newsize)*sizeof(char))))), (b)->buffsize = newsize);
  }
  b->buffer[((b)->n)++] = ((char)((c)));
}
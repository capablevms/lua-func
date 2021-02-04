
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



extern TString * luaS_newlstr(lua_State *, const char *, size_t);
extern unsigned long strlen(const char *);
extern int strcmp(const char *, const char *);

TString *luaS_new (lua_State *L, const char *str) {
  unsigned int i = ((unsigned int)((size_t)(str) & (2147483647 *2U +1U))) % 53;
  int j;
  TString **p = (L->l_G)->strcache[i];
  for (j = 0; j < 2; j++) {
    if (strcmp(str, ((p[j])->contents)) == 0)
      return p[j];
  }

  for (j = 2 - 1; j > 0; j--)
    p[j] = p[j - 1];

  p[0] = luaS_newlstr(L, str, strlen(str));
  return p[0];
}
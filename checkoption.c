
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



extern int luaL_argerror(lua_State *, int, const char *);
extern const char * lua_pushfstring(lua_State *, const char *, ...);
extern void * memcpy(void *restrict, const void *restrict, size_t);
extern int memcmp(const void *, const void *, size_t);

static const char *checkoption (lua_State *L, const char *conv,
                                ptrdiff_t convlen, char *buff) {
  const char *option = "aAbBcCdDeFgGhHIjmMnprRStTuUVwWxXyYzZ%" "||" "EcECExEXEyEY" "OdOeOHOIOmOMOSOuOUOVOwOWOy";
  int oplen = 1;
  for (; *option != '\0' && oplen <= convlen; option += oplen) {
    if (*option == '|')
      oplen++;
    else if (memcmp(conv, option, oplen) == 0) {
      memcpy(buff, conv, oplen);
      buff[oplen] = '\0';
      return conv + oplen;
    }
  }
  luaL_argerror(L, 1,
    lua_pushfstring(L, "invalid conversion specifier '%%%s'", conv));
  return conv;
}
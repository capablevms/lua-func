
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



extern void lua_warning(lua_State *, const char *, int);
extern int dolibrary(lua_State *, const char *);
extern int dostring(lua_State *, const char *, const char *);

extern int runargs (lua_State *L, char **argv, int n) {
  int i;
  for (i = 1; i < n; i++) {
    int option = argv[i][1];
    ((void)0);
    switch (option) {
      case 'e': case 'l': {
        int status;
        const char *extra = argv[i] + 2;
        if (*extra == '\0') extra = argv[++i];
        ((void)0);
        status = (option == 'e')
                 ? dostring(L, extra, "=(command line)")
                 : dolibrary(L, extra);
        if (status != 0) return 0;
        break;
      }
      case 'W':
        lua_warning(L, "@on", 0);
        break;
    }
  }
  return 1;
}
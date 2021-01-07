
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




static int collectargs (char **argv, int *first) {
  int args = 0;
  int i;
  for (i = 1; argv[i] != ((void*)0); i++) {
    *first = i;
    if (argv[i][0] != '-')
        return args;
    switch (argv[i][1]) {
      case '-':
        if (argv[i][2] != '\0')
          return 1;
        *first = i + 1;
        return args;
      case '\0':
        return args;
      case 'E':
        if (argv[i][2] != '\0')
          return 1;
        args |= 16;
        break;
      case 'W':
        if (argv[i][2] != '\0')
          return 1;
        break;
      case 'i':
        args |= 2;
      case 'v':
        if (argv[i][2] != '\0')
          return 1;
        args |= 4;
        break;
      case 'e':
        args |= 8;
      case 'l':
        if (argv[i][2] == '\0') {
          i++;
          if (argv[i] == ((void*)0) || argv[i][0] == '-')
            return 1;
        }
        break;
      default:
        return 1;
    }
  }
  *first = i;
  return args;
}
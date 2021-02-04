
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


const struct {
  lu_byte left;
  lu_byte right;
} priority[] = {
   {10, 10}, {10, 10},
   {11, 11}, {11, 11},
   {14, 13},
   {11, 11}, {11, 11},
   {6, 6}, {4, 4}, {5, 5},
   {7, 7}, {7, 7},
   {9, 8},
   {3, 3}, {3, 3}, {3, 3},
   {3, 3}, {3, 3}, {3, 3},
   {2, 2}, {1, 1}
};

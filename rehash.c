
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



extern void luaH_resize(lua_State *, Table *, unsigned int, unsigned int);
extern unsigned int computesizes(unsigned int *, unsigned int *);
extern int countint(lua_Integer, unsigned int *);
extern int numusehash(const Table *, unsigned int *, unsigned int *);
extern unsigned int numusearray(const Table *, unsigned int *);
extern unsigned int setlimittosize(Table *);

static void rehash (lua_State *L, Table *t, const TValue *ek) {
  unsigned int asize;
  unsigned int na;
  unsigned int nums[((int)((sizeof(int) * 8 - 1))) + 1];
  int i;
  int totaluse;
  for (i = 0; i <= ((int)((sizeof(int) * 8 - 1))); i++) nums[i] = 0;
  setlimittosize(t);
  na = numusearray(t, nums);
  totaluse = na;
  totaluse += numusehash(t, nums, &na);

  if (((((ek))->tt_) == (((3) | ((0) << 4)))))
    na += countint((((ek)->value_).i), nums);
  totaluse++;

  asize = computesizes(nums, &na);

  luaH_resize(L, t, asize, totaluse - na);
}
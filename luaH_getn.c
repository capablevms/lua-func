
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



extern lua_Unsigned hash_search(Table *, lua_Unsigned);
extern const TValue * luaH_getint(Table *, lua_Integer);
extern unsigned int binsearch(const TValue *, unsigned int, unsigned int);
extern unsigned int luaH_realasize(const Table *);
extern unsigned int luaH_realasize(const Table *);
extern int ispow2realasize(const Table *);
extern unsigned int binsearch(const TValue *, unsigned int, unsigned int);
extern int ispow2realasize(const Table *);

lua_Unsigned luaH_getn (Table *t) {
  unsigned int limit = t->alimit;
  if (limit > 0 && (((((((&t->array[limit - 1]))->tt_)) & 0x0F)) == (0))) {

    if (limit >= 2 && !(((((((&t->array[limit - 2]))->tt_)) & 0x0F)) == (0))) {

      if (ispow2realasize(t) && !(((limit - 1) & ((limit - 1) - 1)) == 0)) {
        t->alimit = limit - 1;
        ((t)->flags |= (1 << 7));
      }
      return limit - 1;
    }
    else {
      unsigned int boundary = binsearch(t->array, 0, limit);

      if (ispow2realasize(t) && boundary > luaH_realasize(t) / 2) {
        t->alimit = boundary;
        ((t)->flags |= (1 << 7));
      }
      return boundary;
    }
  }

  if (!((!((t)->flags & (1 << 7))) || ((((t)->alimit) & (((t)->alimit) - 1)) == 0))) {

    if ((((((((&t->array[limit]))->tt_)) & 0x0F)) == (0)))
      return limit;

    limit = luaH_realasize(t);
    if ((((((((&t->array[limit - 1]))->tt_)) & 0x0F)) == (0))) {


      unsigned int boundary = binsearch(t->array, t->alimit, limit);
      t->alimit = boundary;
      return boundary;
    }

  }

  ((void)0);

  if (((t)->lastfree == ((void*)0)) || (((((((luaH_getint(t, ((lua_Integer)(limit + 1)))))->tt_)) & 0x0F)) == (0)))
    return limit;
  else
    return hash_search(t, limit);
}
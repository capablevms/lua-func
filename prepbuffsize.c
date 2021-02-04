
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

typedef struct UBox {
  void *box;
  size_t bsize;
} UBox;


extern void * memcpy(void *restrict, const void *restrict, size_t);
extern void * resizebox(lua_State *, int, size_t);
extern void lua_toclose(lua_State *, int);
extern void lua_rotate(lua_State *, int, int);
extern void newbox(lua_State *);
extern void lua_pushnil(lua_State *);
extern void * resizebox(lua_State *, int, size_t);
extern size_t newbuffsize(luaL_Buffer *, size_t);

extern char *prepbuffsize (luaL_Buffer *B, size_t sz, int boxidx) {
  if (B->size - B->n >= sz)
    return B->b + B->n;
  else {
    lua_State *L = B->L;
    char *newbuff;
    size_t newsize = newbuffsize(B, sz);

    if (((B)->b != (B)->init.b))
      newbuff = (char *)resizebox(L, boxidx, newsize);
    else {
      lua_pushnil(L);
      newbox(L);

      lua_rotate(L, boxidx - 1, 2);
      lua_toclose(L, boxidx);
      newbuff = (char *)resizebox(L, boxidx, newsize);
      memcpy(newbuff, B->b, B->n * sizeof(char));
    }
    B->b = newbuff;
    B->size = newsize;
    return newbuff + B->n;
  }
}
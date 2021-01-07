
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


extern int lua_error(lua_State *);
extern const char * lua_pushstring(lua_State *, const char *);
extern  allocf;
extern void * lua_touserdata(lua_State *, int);
extern lua_Alloc lua_getallocf(lua_State *, void **);

static void *resizebox (lua_State *L, int idx, size_t newsize) {
  void *ud;
  lua_Alloc allocf = lua_getallocf(L, &ud);
  UBox *box = (UBox *)lua_touserdata(L, idx);
  void *temp = allocf(ud, box->box, box->bsize, newsize);
  if (temp == ((void*)0) && newsize > 0) {
    lua_pushstring(L, "" "not enough memory");
    lua_error(L);
  }
  box->box = temp;
  box->bsize = newsize;
  return temp;
}
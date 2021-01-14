
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



extern void freeobj(lua_State *, GCObject *);

extern GCObject **sweeplist (lua_State *L, GCObject **p, int countin,
                             int *countout) {
  global_State *g = (L->l_G);
  int ow = ((g)->currentwhite ^ ((1<<(3)) | (1<<(4))));
  int i;
  int white = ((lu_byte)(((g)->currentwhite & ((1<<(3)) | (1<<(4))))));
  for (i = 0; *p != ((void*)0) && i < countin; i++) {
    GCObject *curr = *p;
    int marked = curr->marked;
    if (((marked) & (ow))) {
      *p = curr->next;
      freeobj(L, curr);
    }
    else {
      curr->marked = ((lu_byte)(((marked & ~(((1<<(5)) | ((1<<(3)) | (1<<(4)))) | 7)) | white)));
      p = &curr->next;
    }
  }
  if (countout)
    *countout = i;
  return (*p == ((void*)0)) ? ((void*)0) : p;
}
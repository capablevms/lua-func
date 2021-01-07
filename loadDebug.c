
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

typedef struct {
  lua_State *L;
  ZIO *Z;
  const char *name;
} LoadState;


extern TString * loadStringN(LoadState *, Proto *);
extern int loadInt(LoadState *);
extern int loadInt(LoadState *);
extern int loadInt(LoadState *);
extern TString * loadStringN(LoadState *, Proto *);
extern void * luaM_malloc_(lua_State *, size_t, int);
extern void luaM_toobig(lua_State *);
extern int loadInt(LoadState *);
extern int loadInt(LoadState *);
extern int loadInt(LoadState *);
extern void * luaM_malloc_(lua_State *, size_t, int);
extern void luaM_toobig(lua_State *);
extern int loadInt(LoadState *);
extern void loadBlock(LoadState *, void *, size_t);
extern void * luaM_malloc_(lua_State *, size_t, int);
extern void luaM_toobig(lua_State *);
extern int loadInt(LoadState *);

static void loadDebug (LoadState *S, Proto *f) {
  int i, n;
  n = loadInt(S);
  f->lineinfo = (((sizeof(n) >= sizeof(size_t) && ((size_t)(((n)))) + 1 > ((size_t)(~(size_t)0))/(sizeof(ls_byte))) ? luaM_toobig(S->L) : ((void)((0)))), ((ls_byte*)(luaM_malloc_(S->L, (n)*sizeof(ls_byte), 0))));
  f->sizelineinfo = n;
  loadBlock(S,f->lineinfo,(n)*sizeof((f->lineinfo)[0]));
  n = loadInt(S);
  f->abslineinfo = (((sizeof(n) >= sizeof(size_t) && ((size_t)(((n)))) + 1 > ((size_t)(~(size_t)0))/(sizeof(AbsLineInfo))) ? luaM_toobig(S->L) : ((void)((0)))), ((AbsLineInfo*)(luaM_malloc_(S->L, (n)*sizeof(AbsLineInfo), 0))));
  f->sizeabslineinfo = n;
  for (i = 0; i < n; i++) {
    f->abslineinfo[i].pc = loadInt(S);
    f->abslineinfo[i].line = loadInt(S);
  }
  n = loadInt(S);
  f->locvars = (((sizeof(n) >= sizeof(size_t) && ((size_t)(((n)))) + 1 > ((size_t)(~(size_t)0))/(sizeof(LocVar))) ? luaM_toobig(S->L) : ((void)((0)))), ((LocVar*)(luaM_malloc_(S->L, (n)*sizeof(LocVar), 0))));
  f->sizelocvars = n;
  for (i = 0; i < n; i++)
    f->locvars[i].varname = ((void*)0);
  for (i = 0; i < n; i++) {
    f->locvars[i].varname = loadStringN(S, f);
    f->locvars[i].startpc = loadInt(S);
    f->locvars[i].endpc = loadInt(S);
  }
  n = loadInt(S);
  for (i = 0; i < n; i++)
    f->upvalues[i].name = loadStringN(S, f);
}
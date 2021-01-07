
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


extern void loadDebug(LoadState *, Proto *);
extern void loadProtos(LoadState *, Proto *);
extern void loadUpvalues(LoadState *, Proto *);
extern void loadConstants(LoadState *, Proto *);
extern void loadCode(LoadState *, Proto *);
extern lu_byte loadByte(LoadState *);
extern lu_byte loadByte(LoadState *);
extern lu_byte loadByte(LoadState *);
extern int loadInt(LoadState *);
extern int loadInt(LoadState *);
extern TString * loadStringN(LoadState *, Proto *);

static void loadFunction (LoadState *S, Proto *f, TString *psource) {
  f->source = loadStringN(S, f);
  if (f->source == ((void*)0))
    f->source = psource;
  f->linedefined = loadInt(S);
  f->lastlinedefined = loadInt(S);
  f->numparams = loadByte(S);
  f->is_vararg = loadByte(S);
  f->maxstacksize = loadByte(S);
  loadCode(S, f);
  loadConstants(S, f);
  loadUpvalues(S, f);
  loadProtos(S, f);
  loadDebug(S, f);
}
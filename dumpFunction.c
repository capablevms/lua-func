
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
  lua_Writer writer;
  void *data;
  int strip;
  int status;
} DumpState;


extern void dumpDebug(DumpState *, const Proto *);
extern void dumpProtos(DumpState *, const Proto *);
extern void dumpUpvalues(DumpState *, const Proto *);
extern void dumpConstants(DumpState *, const Proto *);
extern void dumpCode(DumpState *, const Proto *);
extern void dumpByte(DumpState *, int);
extern void dumpByte(DumpState *, int);
extern void dumpByte(DumpState *, int);
extern void dumpInt(DumpState *, int);
extern void dumpInt(DumpState *, int);
extern void dumpString(DumpState *, const TString *);
extern void dumpString(DumpState *, const TString *);

extern void dumpFunction (DumpState *D, const Proto *f, TString *psource) {
  if (D->strip || f->source == psource)
    dumpString(D, ((void*)0));
  else
    dumpString(D, f->source);
  dumpInt(D, f->linedefined);
  dumpInt(D, f->lastlinedefined);
  dumpByte(D, f->numparams);
  dumpByte(D, f->is_vararg);
  dumpByte(D, f->maxstacksize);
  dumpCode(D, f);
  dumpConstants(D, f);
  dumpUpvalues(D, f);
  dumpProtos(D, f);
  dumpDebug(D, f);
}
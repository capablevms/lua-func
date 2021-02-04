
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


extern void dumpString(DumpState *, const TString *);
extern void dumpInt(DumpState *, int);
extern void dumpInt(DumpState *, int);
extern void dumpInt(DumpState *, int);
extern void dumpString(DumpState *, const TString *);
extern void dumpInt(DumpState *, int);
extern void dumpInt(DumpState *, int);
extern void dumpInt(DumpState *, int);
extern void dumpInt(DumpState *, int);
extern void dumpBlock(DumpState *, const void *, size_t);
extern void dumpInt(DumpState *, int);

extern void dumpDebug (DumpState *D, const Proto *f) {
  int i, n;
  n = (D->strip) ? 0 : f->sizelineinfo;
  dumpInt(D, n);
  dumpBlock(D,f->lineinfo,(n)*sizeof((f->lineinfo)[0]));
  n = (D->strip) ? 0 : f->sizeabslineinfo;
  dumpInt(D, n);
  for (i = 0; i < n; i++) {
    dumpInt(D, f->abslineinfo[i].pc);
    dumpInt(D, f->abslineinfo[i].line);
  }
  n = (D->strip) ? 0 : f->sizelocvars;
  dumpInt(D, n);
  for (i = 0; i < n; i++) {
    dumpString(D, f->locvars[i].varname);
    dumpInt(D, f->locvars[i].startpc);
    dumpInt(D, f->locvars[i].endpc);
  }
  n = (D->strip) ? 0 : f->sizeupvalues;
  dumpInt(D, n);
  for (i = 0; i < n; i++)
    dumpString(D, f->upvalues[i].name);
}
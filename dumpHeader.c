
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


extern void dumpNumber(DumpState *, lua_Number);
extern void dumpInteger(DumpState *, lua_Integer);
extern void dumpByte(DumpState *, int);
extern void dumpByte(DumpState *, int);
extern void dumpByte(DumpState *, int);
extern void dumpBlock(DumpState *, const void *, size_t);
extern void dumpByte(DumpState *, int);
extern void dumpByte(DumpState *, int);
extern void dumpBlock(DumpState *, const void *, size_t);

extern void dumpHeader (DumpState *D) {
  dumpBlock(D,"\x1bLua",sizeof("\x1bLua") - sizeof(char));
  dumpByte(D, (("5"[0]-'0')*16+("4"[0]-'0')));
  dumpByte(D, 0);
  dumpBlock(D,"\x19\x93\r\n\x1a\n",sizeof("\x19\x93\r\n\x1a\n") - sizeof(char));
  dumpByte(D, sizeof(Instruction));
  dumpByte(D, sizeof(lua_Integer));
  dumpByte(D, sizeof(lua_Number));
  dumpInteger(D, 0x5678);
  dumpNumber(D, ((lua_Number)((370.5))));
}
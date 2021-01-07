
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


extern void error(LoadState *, const char *);
extern lua_Number loadNumber(LoadState *);
extern void error(LoadState *, const char *);
extern lua_Integer loadInteger(LoadState *);
extern void fchecksize(LoadState *, size_t, const char *);
extern void fchecksize(LoadState *, size_t, const char *);
extern void fchecksize(LoadState *, size_t, const char *);
extern void checkliteral(LoadState *, const char *, const char *);
extern void error(LoadState *, const char *);
extern lu_byte loadByte(LoadState *);
extern void error(LoadState *, const char *);
extern lu_byte loadByte(LoadState *);
extern void checkliteral(LoadState *, const char *, const char *);

static void checkHeader (LoadState *S) {

  checkliteral(S, &"\x1bLua"[1], "not a binary chunk");
  if (loadByte(S) != (("5"[0]-'0')*16+("4"[0]-'0')))
    error(S, "version mismatch");
  if (loadByte(S) != 0)
    error(S, "format mismatch");
  checkliteral(S, "\x19\x93\r\n\x1a\n", "corrupted chunk");
  fchecksize(S,sizeof(Instruction),"Instruction");
  fchecksize(S,sizeof(lua_Integer),"lua_Integer");
  fchecksize(S,sizeof(lua_Number),"lua_Number");
  if (loadInteger(S) != 0x5678)
    error(S, "integer format mismatch");
  if (loadNumber(S) != ((lua_Number)((370.5))))
    error(S, "float format mismatch");
}
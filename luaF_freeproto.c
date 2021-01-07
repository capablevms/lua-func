
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



extern void luaM_free_(lua_State *, void *, size_t);
extern void luaM_free_(lua_State *, void *, size_t);
extern void luaM_free_(lua_State *, void *, size_t);
extern void luaM_free_(lua_State *, void *, size_t);
extern void luaM_free_(lua_State *, void *, size_t);
extern void luaM_free_(lua_State *, void *, size_t);
extern void luaM_free_(lua_State *, void *, size_t);
extern void luaM_free_(lua_State *, void *, size_t);

void luaF_freeproto (lua_State *L, Proto *f) {
  luaM_free_(L, (f->code), (f->sizecode)*sizeof(*(f->code)));
  luaM_free_(L, (f->p), (f->sizep)*sizeof(*(f->p)));
  luaM_free_(L, (f->k), (f->sizek)*sizeof(*(f->k)));
  luaM_free_(L, (f->lineinfo), (f->sizelineinfo)*sizeof(*(f->lineinfo)));
  luaM_free_(L, (f->abslineinfo), (f->sizeabslineinfo)*sizeof(*(f->abslineinfo)));
  luaM_free_(L, (f->locvars), (f->sizelocvars)*sizeof(*(f->locvars)));
  luaM_free_(L, (f->upvalues), (f->sizeupvalues)*sizeof(*(f->upvalues)));
  luaM_free_(L, (f), sizeof(*(f)));
}
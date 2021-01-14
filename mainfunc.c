
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

typedef struct BlockCnt {
  struct BlockCnt *previous;
  int firstlabel;
  int firstgoto;
  lu_byte nactvar;
  lu_byte upval;
  lu_byte isloop;
  lu_byte insidetbc;
} BlockCnt;


extern void close_func(LexState *);
extern void check(LexState *, int);
extern void statlist(LexState *);
extern void luaX_next(LexState *);
extern void luaC_barrier_(lua_State *, GCObject *, GCObject *);
extern Upvaldesc * allocupvalue(FuncState *);
extern void setvararg(FuncState *, int);
extern void open_func(LexState *, FuncState *, BlockCnt *);

extern void mainfunc (LexState *ls, FuncState *fs) {
  BlockCnt bl;
  Upvaldesc *env;
  open_func(ls, fs, &bl);
  setvararg(fs, 0);
  env = allocupvalue(fs);
  env->instack = 1;
  env->idx = 0;
  env->kind = 0;
  env->name = ls->envn;
  ( ((((fs->f)->marked) & ((1<<(5)))) && (((env->name)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(ls->L,(&(((union GCUnion *)((fs->f)))->gc)),(&(((union GCUnion *)((env->name)))->gc))) : ((void)((0))));
  luaX_next(ls);
  statlist(ls);
  check(ls, TK_EOS);
  close_func(ls);
}
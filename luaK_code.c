
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



extern void savelineinfo(FuncState *, Proto *, int);
extern void * luaM_growaux_(lua_State *, void *, int, int *, int, int, const char *);

int luaK_code (FuncState *fs, Instruction i) {
  Proto *f = fs->f;

  ((f->code)=((Instruction *)(luaM_growaux_(fs->ls->L,f->code,fs->pc,&(f->sizecode),sizeof(Instruction), ((((size_t)((2147483647))) <= ((size_t)(~(size_t)0))/sizeof(Instruction)) ? (2147483647) : ((unsigned int)(((((size_t)(~(size_t)0))/sizeof(Instruction)))))),"opcodes"))));

  f->code[fs->pc++] = i;
  savelineinfo(fs, f, fs->ls->lastline);
  return fs->pc - 1;
}
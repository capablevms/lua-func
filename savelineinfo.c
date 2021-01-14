
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



extern void * luaM_growaux_(lua_State *, void *, int, int *, int, int, const char *);
extern void * luaM_growaux_(lua_State *, void *, int, int *, int, int, const char *);
extern int abs(int);

extern void savelineinfo (FuncState *fs, Proto *f, int line) {
  int linedif = line - fs->previousline;
  int pc = fs->pc - 1;
  if (abs(linedif) >= 0x80 || fs->iwthabs++ > 120) {
    ((f->abslineinfo)=((AbsLineInfo *)(luaM_growaux_(fs->ls->L,f->abslineinfo,fs->nabslineinfo,&(f->sizeabslineinfo),sizeof(AbsLineInfo), ((((size_t)((2147483647))) <= ((size_t)(~(size_t)0))/sizeof(AbsLineInfo)) ? (2147483647) : ((unsigned int)(((((size_t)(~(size_t)0))/sizeof(AbsLineInfo)))))),"lines"))));

    f->abslineinfo[fs->nabslineinfo].pc = pc;
    f->abslineinfo[fs->nabslineinfo++].line = line;
    linedif = (-0x80);
    fs->iwthabs = 0;
  }
  ((f->lineinfo)=((ls_byte *)(luaM_growaux_(fs->ls->L,f->lineinfo,pc,&(f->sizelineinfo),sizeof(ls_byte), ((((size_t)((2147483647))) <= ((size_t)(~(size_t)0))/sizeof(ls_byte)) ? (2147483647) : ((unsigned int)(((((size_t)(~(size_t)0))/sizeof(ls_byte)))))),"opcodes"))));

  f->lineinfo[pc] = linedif;
  fs->previousline = line;
}
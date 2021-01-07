
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

typedef struct BuffFS {
  lua_State *L;
  int pushed;
  int blen;
  char space[200];
} BuffFS;


extern void clearbuff(BuffFS *);
extern void addstr2buff(BuffFS *, const char *, size_t);
extern unsigned long strlen(const char *);
extern void luaG_runerror(lua_State *, const char *, ...);
extern void addstr2buff(BuffFS *, const char *, size_t);
extern void addstr2buff(BuffFS *, const char *, size_t);
extern int luaO_utf8esc(char *, unsigned long);
extern int snprintf(char *restrict, size_t, const char *restrict, ...);
extern char * getbuff(BuffFS *, int);
extern void addnum2buff(BuffFS *, TValue *);
extern void addnum2buff(BuffFS *, TValue *);
extern void addnum2buff(BuffFS *, TValue *);
extern void addstr2buff(BuffFS *, const char *, size_t);
extern void addstr2buff(BuffFS *, const char *, size_t);
extern unsigned long strlen(const char *);
extern void addstr2buff(BuffFS *, const char *, size_t);
extern char * strchr(const char *, int);

const char *luaO_pushvfstring (lua_State *L, const char *fmt, va_list argp) {
  BuffFS buff;
  const char *e;
  buff.pushed = buff.blen = 0;
  buff.L = L;
  while ((e = strchr(fmt, '%')) != ((void*)0)) {
    addstr2buff(&buff, fmt, e - fmt);
    switch (*(e + 1)) {
      case 's': {
        const char *s = __builtin_va_arg(argp, char *);
        if (s == ((void*)0)) s = "(null)";
        addstr2buff(&buff, s, strlen(s));
        break;
      }
      case 'c': {
        char c = ((unsigned char)((__builtin_va_arg(argp, int))));
        addstr2buff(&buff, &c, sizeof(char));
        break;
      }
      case 'd': {
        TValue num;
        { TValue *io=(&num); ((io)->value_).i=(__builtin_va_arg(argp, int)); ((io)->tt_=(((3) | ((0) << 4)))); };
        addnum2buff(&buff, &num);
        break;
      }
      case 'I': {
        TValue num;
        { TValue *io=(&num); ((io)->value_).i=(((lua_Integer)(__builtin_va_arg(argp, l_uacInt)))); ((io)->tt_=(((3) | ((0) << 4)))); };
        addnum2buff(&buff, &num);
        break;
      }
      case 'f': {
        TValue num;
        { TValue *io=(&num); ((io)->value_).n=(((lua_Number)((__builtin_va_arg(argp, l_uacNumber))))); ((io)->tt_=(((3) | ((1) << 4)))); };
        addnum2buff(&buff, &num);
        break;
      }
      case 'p': {
        const int sz = 3 * sizeof(void*) + 8;
        char *bf = getbuff(&buff, sz);
        void *p = __builtin_va_arg(argp, void *);
        int len = snprintf(bf,sz,"%p",p);
        ((&buff)->blen += (len));
        break;
      }
      case 'U': {
        char bf[8];
        int len = luaO_utf8esc(bf, __builtin_va_arg(argp, long));
        addstr2buff(&buff, bf + 8 - len, len);
        break;
      }
      case '%': {
        addstr2buff(&buff, "%", 1);
        break;
      }
      default: {
        luaG_runerror(L, "invalid option '%%%c' to 'lua_pushfstring'",
                         *(e + 1));
      }
    }
    fmt = e + 2;
  }
  addstr2buff(&buff, fmt, strlen(fmt));
  clearbuff(&buff);
  ((void)0);
  return ((((&((((union GCUnion *)(((((&(L->top - 1)->val))->value_).gc))))->ts))))->contents);
}
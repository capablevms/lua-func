
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
  FILE *f;
  int c;
  int n;
  char buff[200 + 1];
} RN;


extern void lua_pushnil(lua_State *);
extern size_t lua_stringtonumber(lua_State *, const char *);
extern int ungetc(int, FILE *);
extern int readdigits(RN *, int);
extern int test2(RN *, const char *);
extern int test2(RN *, const char *);
extern int readdigits(RN *, int);
extern int test2(RN *, const char *);
extern int readdigits(RN *, int);
extern int test2(RN *, const char *);
extern int test2(RN *, const char *);
extern int test2(RN *, const char *);
extern const unsigned short ** __ctype_b_loc();
extern int getc(FILE *);
extern struct lconv * localeconv();

static int read_number (lua_State *L, FILE *f) {
  RN rn;
  int count = 0;
  int hex = 0;
  char decp[2];
  rn.f = f; rn.n = 0;
  decp[0] = (localeconv()->decimal_point[0]);
  decp[1] = '.';
  ((void)0);
  do { rn.c = getc(rn.f); } while (((*__ctype_b_loc ())[(int) ((rn.c))] & (unsigned short int) _ISspace));
  test2(&rn, "-+");
  if (test2(&rn, "00")) {
    if (test2(&rn, "xX")) hex = 1;
    else count = 1;
  }
  count += readdigits(&rn, hex);
  if (test2(&rn, decp))
    count += readdigits(&rn, hex);
  if (count > 0 && test2(&rn, (hex ? "pP" : "eE"))) {
    test2(&rn, "-+");
    readdigits(&rn, 0);
  }
  ungetc(rn.c, rn.f);
  ((void)0);
  rn.buff[rn.n] = '\0';
  if (lua_stringtonumber(L, rn.buff))
    return 1;
  else {
   lua_pushnil(L);
   return 0;
  }
}
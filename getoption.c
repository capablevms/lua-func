
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

typedef struct Header {
  lua_State *L;
  int islittle;
  int maxalign;
} Header;

typedef enum KOption {
  Kint,
  Kuint,
  Kfloat,
  Kchar,
  Kstring,
  Kzstr,
  Kpadding,
  Kpaddalign,
  Knop
} KOption;

static const union {
  int dummy;
  char little;
} nativeendian = {1};

struct cD {
  char c;
  union { double d; void *p; lua_Integer i; lua_Number n; } u;
};

extern int luaL_error(lua_State *, const char *, ...);
extern int getnumlimit(Header *, const char **, int);
extern int luaL_error(lua_State *, const char *, ...);
extern int getnum(const char **, int);
extern int getnumlimit(Header *, const char **, int);
extern int getnumlimit(Header *, const char **, int);
extern int getnumlimit(Header *, const char **, int);

static KOption getoption (Header *h, const char **fmt, int *size) {
  int opt = *((*fmt)++);
  *size = 0;
  switch (opt) {
    case 'b': *size = sizeof(char); return Kint;
    case 'B': *size = sizeof(char); return Kuint;
    case 'h': *size = sizeof(short); return Kint;
    case 'H': *size = sizeof(short); return Kuint;
    case 'l': *size = sizeof(long); return Kint;
    case 'L': *size = sizeof(long); return Kuint;
    case 'j': *size = sizeof(lua_Integer); return Kint;
    case 'J': *size = sizeof(lua_Integer); return Kuint;
    case 'T': *size = sizeof(size_t); return Kuint;
    case 'f': *size = sizeof(float); return Kfloat;
    case 'd': *size = sizeof(double); return Kfloat;
    case 'n': *size = sizeof(lua_Number); return Kfloat;
    case 'i': *size = getnumlimit(h, fmt, sizeof(int)); return Kint;
    case 'I': *size = getnumlimit(h, fmt, sizeof(int)); return Kuint;
    case 's': *size = getnumlimit(h, fmt, sizeof(size_t)); return Kstring;
    case 'c':
      *size = getnum(fmt, -1);
      if (*size == -1)
        luaL_error(h->L, "missing size for format option 'c'");
      return Kchar;
    case 'z': return Kzstr;
    case 'x': *size = 1; return Kpadding;
    case 'X': return Kpaddalign;
    case ' ': break;
    case '<': h->islittle = 1; break;
    case '>': h->islittle = 0; break;
    case '=': h->islittle = nativeendian.little; break;
    case '!': h->maxalign = getnumlimit(h, fmt, (__builtin_offsetof(struct cD, u))); break;
    default: luaL_error(h->L, "invalid format option '%c'", opt);
  }
  return Knop;
}
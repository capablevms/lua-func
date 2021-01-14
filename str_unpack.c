
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

typedef union Ftypes {
  float f;
  double d;
  lua_Number n;
} Ftypes;
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
typedef struct Header {
  lua_State *L;
  int islittle;
  int maxalign;
} Header;


extern void lua_pushinteger(lua_State *, lua_Integer);
extern const char * lua_pushlstring(lua_State *, const char *, size_t);
extern int luaL_argerror(lua_State *, int, const char *);
extern unsigned long strlen(const char *);
extern const char * lua_pushlstring(lua_State *, const char *, size_t);
extern int luaL_argerror(lua_State *, int, const char *);
extern lua_Integer unpackint(lua_State *, const char *, int, int, int);
extern const char * lua_pushlstring(lua_State *, const char *, size_t);
extern void lua_pushnumber(lua_State *, lua_Number);
extern void copywithendian(char *, const char *, int, int);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern lua_Integer unpackint(lua_State *, const char *, int, int, int);
extern void luaL_checkstack(lua_State *, int, const char *);
extern int luaL_argerror(lua_State *, int, const char *);
extern KOption getdetails(Header *, size_t, const char **, int *, int *);
extern void initheader(lua_State *, Header *);
extern int luaL_argerror(lua_State *, int, const char *);
extern size_t posrelatI(lua_Integer, size_t);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

extern int str_unpack (lua_State *L) {
  Header h;
  const char *fmt = (luaL_checklstring(L, (1), ((void*)0)));
  size_t ld;
  const char *data = luaL_checklstring(L, 2, &ld);
  size_t pos = posrelatI(luaL_optinteger(L, 3, 1), ld) - 1;
  int n = 0;
  ((void)((pos <= ld) || luaL_argerror(L, (3), ("initial position out of string"))));
  initheader(L, &h);
  while (*fmt != '\0') {
    int size, ntoalign;
    KOption opt = getdetails(&h, pos, &fmt, &size, &ntoalign);
    ((void)(((size_t)ntoalign + size <= ld - pos) || luaL_argerror(L, (2), ("data string too short"))));

    pos += ntoalign;

    luaL_checkstack(L, 2, "too many results");
    n++;
    switch (opt) {
      case Kint:
      case Kuint: {
        lua_Integer res = unpackint(L, data + pos, h.islittle, size,
                                       (opt == Kint));
        lua_pushinteger(L, res);
        break;
      }
      case Kfloat: {
        Ftypes u;
        lua_Number num;
        copywithendian((char *)&u, data + pos, size, h.islittle);
        if (size == sizeof(u.f)) num = (lua_Number)u.f;
        else if (size == sizeof(u.d)) num = (lua_Number)u.d;
        else num = u.n;
        lua_pushnumber(L, num);
        break;
      }
      case Kchar: {
        lua_pushlstring(L, data + pos, size);
        break;
      }
      case Kstring: {
        size_t len = (size_t)unpackint(L, data + pos, h.islittle, size, 0);
        ((void)((len <= ld - pos - size) || luaL_argerror(L, (2), ("data string too short"))));
        lua_pushlstring(L, data + pos + size, len);
        pos += len;
        break;
      }
      case Kzstr: {
        size_t len = strlen(data + pos);
        ((void)((pos + len < ld) || luaL_argerror(L, (2), ("unfinished string for format 'z'"))));

        lua_pushlstring(L, data + pos, len);
        pos += len + 1;
        break;
      }
      case Kpaddalign: case Kpadding: case Knop:
        n--;
        break;
    }
    pos += size;
  }
  lua_pushinteger(L, pos + 1);
  return n + 1;
}
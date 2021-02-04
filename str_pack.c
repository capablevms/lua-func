
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


extern void luaL_pushresult(luaL_Buffer *);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern void luaL_addlstring(luaL_Buffer *, const char *, size_t);
extern int luaL_argerror(lua_State *, int, const char *);
extern unsigned long strlen(const char *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern void luaL_addlstring(luaL_Buffer *, const char *, size_t);
extern void packint(luaL_Buffer *, lua_Unsigned, int, int, int);
extern int luaL_argerror(lua_State *, int, const char *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern void luaL_addlstring(luaL_Buffer *, const char *, size_t);
extern int luaL_argerror(lua_State *, int, const char *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern void copywithendian(char *, const char *, int, int);
extern lua_Number luaL_checknumber(lua_State *, int);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern void packint(luaL_Buffer *, lua_Unsigned, int, int, int);
extern int luaL_argerror(lua_State *, int, const char *);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern void packint(luaL_Buffer *, lua_Unsigned, int, int, int);
extern int luaL_argerror(lua_State *, int, const char *);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern KOption getdetails(Header *, size_t, const char **, int *, int *);
extern void luaL_buffinit(lua_State *, luaL_Buffer *);
extern void lua_pushnil(lua_State *);
extern void initheader(lua_State *, Header *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);

extern int str_pack (lua_State *L) {
  luaL_Buffer b;
  Header h;
  const char *fmt = (luaL_checklstring(L, (1), ((void*)0)));
  int arg = 1;
  size_t totalsize = 0;
  initheader(L, &h);
  lua_pushnil(L);
  luaL_buffinit(L, &b);
  while (*fmt != '\0') {
    int size, ntoalign;
    KOption opt = getdetails(&h, totalsize, &fmt, &size, &ntoalign);
    totalsize += ntoalign + size;
    while (ntoalign-- > 0)
     ((void)((&b)->n < (&b)->size || luaL_prepbuffsize((&b), 1)), ((&b)->b[(&b)->n++] = (0x00)));
    arg++;
    switch (opt) {
      case Kint: {
        lua_Integer n = luaL_checkinteger(L, arg);
        if (size < ((int)sizeof(lua_Integer))) {
          lua_Integer lim = (lua_Integer)1 << ((size * 8) - 1);
          ((void)((-lim <= n && n < lim) || luaL_argerror(L, (arg), ("integer overflow"))));
        }
        packint(&b, (lua_Unsigned)n, h.islittle, size, (n < 0));
        break;
      }
      case Kuint: {
        lua_Integer n = luaL_checkinteger(L, arg);
        if (size < ((int)sizeof(lua_Integer)))
          ((void)(((lua_Unsigned)n < ((lua_Unsigned)1 << (size * 8))) || luaL_argerror(L, (arg), ("unsigned overflow"))));

        packint(&b, (lua_Unsigned)n, h.islittle, size, 0);
        break;
      }
      case Kfloat: {
        Ftypes u;
        char *buff = luaL_prepbuffsize(&b, size);
        lua_Number n = luaL_checknumber(L, arg);
        if (size == sizeof(u.f)) u.f = (float)n;
        else if (size == sizeof(u.d)) u.d = (double)n;
        else u.n = n;

        copywithendian(buff, (char *)&u, size, h.islittle);
        ((&b)->n += (size));
        break;
      }
      case Kchar: {
        size_t len;
        const char *s = luaL_checklstring(L, arg, &len);
        ((void)((len <= (size_t)size) || luaL_argerror(L, (arg), ("string longer than given size"))));

        luaL_addlstring(&b, s, len);
        while (len++ < (size_t)size)
          ((void)((&b)->n < (&b)->size || luaL_prepbuffsize((&b), 1)), ((&b)->b[(&b)->n++] = (0x00)));
        break;
      }
      case Kstring: {
        size_t len;
        const char *s = luaL_checklstring(L, arg, &len);
        ((void)((size >= (int)sizeof(size_t) || len < ((size_t)1 << (size * 8))) || luaL_argerror(L, (arg), ("string length does not fit in given size"))));


        packint(&b, (lua_Unsigned)len, h.islittle, size, 0);
        luaL_addlstring(&b, s, len);
        totalsize += len;
        break;
      }
      case Kzstr: {
        size_t len;
        const char *s = luaL_checklstring(L, arg, &len);
        ((void)((strlen(s) == len) || luaL_argerror(L, (arg), ("string contains zeros"))));
        luaL_addlstring(&b, s, len);
        ((void)((&b)->n < (&b)->size || luaL_prepbuffsize((&b), 1)), ((&b)->b[(&b)->n++] = ('\0')));
        totalsize += len + 1;
        break;
      }
      case Kpadding: ((void)((&b)->n < (&b)->size || luaL_prepbuffsize((&b), 1)), ((&b)->b[(&b)->n++] = (0x00)));
      case Kpaddalign: case Knop:
        arg--;
        break;
    }
  }
  luaL_pushresult(&b);
  return 1;
}
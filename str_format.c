
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



extern void luaL_pushresult(luaL_Buffer *);
extern int luaL_error(lua_State *, const char *, ...);
extern void lua_settop(lua_State *, int);
extern int snprintf(char *restrict, size_t, const char *restrict, ...);
extern void luaL_addvalue(luaL_Buffer *);
extern char * strchr(const char *, int);
extern int luaL_argerror(lua_State *, int, const char *);
extern unsigned long strlen(const char *);
extern void luaL_addvalue(luaL_Buffer *);
extern const char * luaL_tolstring(lua_State *, int, size_t *);
extern void addliteral(lua_State *, luaL_Buffer *, int);
extern int luaL_error(lua_State *, const char *, ...);
extern int snprintf(char *restrict, size_t, const char *restrict, ...);
extern unsigned long strlen(const char *);
extern const void * lua_topointer(lua_State *, int);
extern int snprintf(char *restrict, size_t, const char *restrict, ...);
extern void addlenmod(char *, const char *);
extern lua_Number luaL_checknumber(lua_State *, int);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern int snprintf(char *restrict, size_t, const char *restrict, ...);
extern lua_Number luaL_checknumber(lua_State *, int);
extern void addlenmod(char *, const char *);
extern int snprintf(char *restrict, size_t, const char *restrict, ...);
extern void addlenmod(char *, const char *);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern int snprintf(char *restrict, size_t, const char *restrict, ...);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern const char * scanformat(lua_State *, const char *, char *);
extern int luaL_argerror(lua_State *, int, const char *);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern char * luaL_prepbuffsize(luaL_Buffer *, size_t);
extern void luaL_buffinit(lua_State *, luaL_Buffer *);
extern const char * luaL_checklstring(lua_State *, int, size_t *);
extern int lua_gettop(lua_State *);

static int str_format (lua_State *L) {
  int top = lua_gettop(L);
  int arg = 1;
  size_t sfl;
  const char *strfrmt = luaL_checklstring(L, arg, &sfl);
  const char *strfrmt_end = strfrmt+sfl;
  luaL_Buffer b;
  luaL_buffinit(L, &b);
  while (strfrmt < strfrmt_end) {
    if (*strfrmt != '%')
      ((void)((&b)->n < (&b)->size || luaL_prepbuffsize((&b), 1)), ((&b)->b[(&b)->n++] = (*strfrmt++)));
    else if (*++strfrmt == '%')
      ((void)((&b)->n < (&b)->size || luaL_prepbuffsize((&b), 1)), ((&b)->b[(&b)->n++] = (*strfrmt++)));
    else {
      char form[32];
      int maxitem = 120;
      char *buff = luaL_prepbuffsize(&b, maxitem);
      int nb = 0;
      if (++arg > top)
        return luaL_argerror(L, arg, "no value");
      strfrmt = scanformat(L, strfrmt, form);
      switch (*strfrmt++) {
        case 'c': {
          nb = snprintf(buff,maxitem,form,(int)luaL_checkinteger(L, arg));
          break;
        }
        case 'd': case 'i':
        case 'o': case 'u': case 'x': case 'X': {
          lua_Integer n = luaL_checkinteger(L, arg);
          addlenmod(form, "ll");
          nb = snprintf(buff,maxitem,form,(long long)n);
          break;
        }
        case 'a': case 'A':
          addlenmod(form, "");
          nb = ((void)L, snprintf(buff,maxitem,form,(double)(luaL_checknumber(L, arg))));

          break;
        case 'f':
          maxitem = (110 + (308));
          buff = luaL_prepbuffsize(&b, maxitem);

        case 'e': case 'E': case 'g': case 'G': {
          lua_Number n = luaL_checknumber(L, arg);
          addlenmod(form, "");
          nb = snprintf(buff,maxitem,form,(double)n);
          break;
        }
        case 'p': {
          const void *p = lua_topointer(L, arg);
          if (p == ((void*)0)) {
            p = "(null)";
            form[strlen(form) - 1] = 's';
          }
          nb = snprintf(buff,maxitem,form,p);
          break;
        }
        case 'q': {
          if (form[2] != '\0')
            return luaL_error(L, "specifier '%%q' cannot have modifiers");
          addliteral(L, &b, arg);
          break;
        }
        case 's': {
          size_t l;
          const char *s = luaL_tolstring(L, arg, &l);
          if (form[2] == '\0')
            luaL_addvalue(&b);
          else {
            ((void)((l == strlen(s)) || luaL_argerror(L, (arg), ("string contains zeros"))));
            if (!strchr(form, '.') && l >= 100) {

              luaL_addvalue(&b);
            }
            else {
              nb = snprintf(buff,maxitem,form,s);
              lua_settop(L, -(1)-1);
            }
          }
          break;
        }
        default: {
          return luaL_error(L, "invalid conversion '%s' to 'format'", form);
        }
      }
      ((void)0);
      ((&b)->n += (nb));
    }
  }
  luaL_pushresult(&b);
  return 1;
}
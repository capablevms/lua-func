
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



extern TString * luaX_newstring(LexState *, const char *, size_t);
extern int luaZ_fill(ZIO *);
extern int luaZ_fill(ZIO *);
extern void save(LexState *, int);
extern void inclinenumber(LexState *);
extern void save(LexState *, int);
extern int luaZ_fill(ZIO *);
extern void save(LexState *, int);
extern size_t skip_sep(LexState *);
extern void lexerror(LexState *, const char *, int);
extern const char * luaO_pushfstring(lua_State *, const char *, ...);
extern void inclinenumber(LexState *);
extern int luaZ_fill(ZIO *);
extern void save(LexState *, int);

extern void read_long_string (LexState *ls, SemInfo *seminfo, size_t sep) {
  int line = ls->linenumber;
  (save(ls, ls->current), (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z))));
  if ((ls->current == '\n' || ls->current == '\r'))
    inclinenumber(ls);
  for (;;) {
    switch (ls->current) {
      case (-1): {
        const char *what = (seminfo ? "string" : "comment");
        const char *msg = luaO_pushfstring(ls->L,
                     "unfinished long %s (starting at line %d)", what, line);
        lexerror(ls, msg, TK_EOS);
        break;
      }
      case ']': {
        if (skip_sep(ls) == sep) {
          (save(ls, ls->current), (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z))));
          goto endloop;
        }
        break;
      }
      case '\n': case '\r': {
        save(ls, '\n');
        inclinenumber(ls);
        if (!seminfo) ((ls->buff)->n = 0);
        break;
      }
      default: {
        if (seminfo) (save(ls, ls->current), (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z))));
        else (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z)));
      }
    }
  } endloop:
  if (seminfo)
    seminfo->ts = luaX_newstring(ls, ((ls->buff)->buffer) + sep,
                                     ((ls->buff)->n) - 2 * sep);
}
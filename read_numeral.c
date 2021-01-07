
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



extern void lexerror(LexState *, const char *, int);
extern size_t luaO_str2num(const char *, TValue *);
extern void save(LexState *, int);
extern int luaZ_fill(ZIO *);
extern void save(LexState *, int);
extern int luaZ_fill(ZIO *);
extern void save(LexState *, int);
extern int check_next2(LexState *, const char *);
extern int check_next2(LexState *, const char *);
extern int check_next2(LexState *, const char *);
extern int luaZ_fill(ZIO *);
extern void save(LexState *, int);

static int read_numeral (LexState *ls, SemInfo *seminfo) {
  TValue obj;
  const char *expo = "Ee";
  int first = ls->current;
  ((void)0);
  (save(ls, ls->current), (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z))));
  if (first == '0' && check_next2(ls, "xX"))
    expo = "Pp";
  for (;;) {
    if (check_next2(ls, expo))
      check_next2(ls, "-+");
    else if ((luai_ctype_[(ls->current)+1] & ((1 << (4)))) || ls->current == '.')
      (save(ls, ls->current), (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z))));
    else break;
  }
  if ((luai_ctype_[(ls->current)+1] & ((1 << (0)))))
    (save(ls, ls->current), (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z))));
  save(ls, '\0');
  if (luaO_str2num(((ls->buff)->buffer), &obj) == 0)
    lexerror(ls, "malformed number", TK_FLT);
  if (((((&obj))->tt_) == (((3) | ((0) << 4))))) {
    seminfo->i = (((&obj)->value_).i);
    return TK_INT;
  }
  else {
    ((void)0);
    seminfo->r = (((&obj)->value_).n);
    return TK_FLT;
  }
}
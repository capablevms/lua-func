
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
extern void save(LexState *, int);
extern int luaZ_fill(ZIO *);
extern void save(LexState *, int);
extern void save(LexState *, int);
extern int luaZ_fill(ZIO *);
extern int readdecesc(LexState *);
extern void esccheck(LexState *, int, const char *);
extern int luaZ_fill(ZIO *);
extern void inclinenumber(LexState *);
extern int luaZ_fill(ZIO *);
extern void inclinenumber(LexState *);
extern void utf8esc(LexState *);
extern int readhexaesc(LexState *);
extern int luaZ_fill(ZIO *);
extern void save(LexState *, int);
extern void lexerror(LexState *, const char *, int);
extern void lexerror(LexState *, const char *, int);
extern int luaZ_fill(ZIO *);
extern void save(LexState *, int);

extern void read_string (LexState *ls, int del, SemInfo *seminfo) {
  (save(ls, ls->current), (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z))));
  while (ls->current != del) {
    switch (ls->current) {
      case (-1):
        lexerror(ls, "unfinished string", TK_EOS);
        break;
      case '\n':
      case '\r':
        lexerror(ls, "unfinished string", TK_STRING);
        break;
      case '\\': {
        int c;
        (save(ls, ls->current), (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z))));
        switch (ls->current) {
          case 'a': c = '\a'; goto read_save;
          case 'b': c = '\b'; goto read_save;
          case 'f': c = '\f'; goto read_save;
          case 'n': c = '\n'; goto read_save;
          case 'r': c = '\r'; goto read_save;
          case 't': c = '\t'; goto read_save;
          case 'v': c = '\v'; goto read_save;
          case 'x': c = readhexaesc(ls); goto read_save;
          case 'u': utf8esc(ls); goto no_save;
          case '\n': case '\r':
            inclinenumber(ls); c = '\n'; goto only_save;
          case '\\': case '\"': case '\'':
            c = ls->current; goto read_save;
          case (-1): goto no_save;
          case 'z': {
            ((ls->buff)->n -= (1));
            (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z)));
            while ((luai_ctype_[(ls->current)+1] & ((1 << (3))))) {
              if ((ls->current == '\n' || ls->current == '\r')) inclinenumber(ls);
              else (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z)));
            }
            goto no_save;
          }
          default: {
            esccheck(ls, (luai_ctype_[(ls->current)+1] & ((1 << (1)))), "invalid escape sequence");
            c = readdecesc(ls);
            goto only_save;
          }
        }
       read_save:
         (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z)));

       only_save:
         ((ls->buff)->n -= (1));
         save(ls, c);

       no_save: break;
      }
      default:
        (save(ls, ls->current), (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z))));
    }
  }
  (save(ls, ls->current), (ls->current = (((ls->z)->n--)>0 ? ((unsigned char)((*(ls->z)->p++))) : luaZ_fill(ls->z))));
  seminfo->ts = luaX_newstring(ls, ((ls->buff)->buffer) + 1,
                                   ((ls->buff)->n) - 2);
}
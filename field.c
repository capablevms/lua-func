
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

typedef struct ConsControl {
  expdesc v;
  expdesc *t;
  int nh;
  int na;
  int tostore;
} ConsControl;


extern void listfield(LexState *, ConsControl *);
extern void recfield(LexState *, ConsControl *);
extern void recfield(LexState *, ConsControl *);
extern void listfield(LexState *, ConsControl *);
extern int luaX_lookahead(LexState *);

static void field (LexState *ls, ConsControl *cc) {

  switch(ls->t.token) {
    case TK_NAME: {
      if (luaX_lookahead(ls) != '=')
        listfield(ls, cc);
      else
        recfield(ls, cc);
      break;
    }
    case '[': {
      recfield(ls, cc);
      break;
    }
    default: {
      listfield(ls, cc);
      break;
    }
  }
}
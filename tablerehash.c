
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




static void tablerehash (TString **vect, int osize, int nsize) {
  int i;
  for (i = osize; i < nsize; i++)
    vect[i] = ((void*)0);
  for (i = 0; i < osize; i++) {
    TString *p = vect[i];
    vect[i] = ((void*)0);
    while (p) {
      TString *hnext = p->u.hnext;
      unsigned int h = (((((int)(((p->hash) & ((nsize)-1)))))));
      p->u.hnext = vect[h];
      vect[h] = p;
      p = hnext;
    }
  }
}
#include <ctype.h>
#include <string.h>

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

extern int l_strcmp (const TString *ls, const TString *rs) {
  const char *l = ((ls)->contents);
  size_t ll = ((ls)->tt == ((4) | ((0) << 4)) ? (ls)->shrlen : (ls)->u.lnglen);
  const char *r = ((rs)->contents);
  size_t lr = ((rs)->tt == ((4) | ((0) << 4)) ? (rs)->shrlen : (rs)->u.lnglen);
  for (;;) {
    int temp = strcoll(l, r);
    if (temp != 0)
      return temp;
    else {
      size_t len = strlen(l);
      if (len == lr)
        return (len == ll) ? 0 : 1;
      else if (len == ll)
        return -1;

      len++;
      l += len; ll -= len; r += len; lr -= len;
    }
  }
}

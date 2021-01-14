
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



extern const unsigned short ** __ctype_b_loc();
extern const unsigned short ** __ctype_b_loc();
extern const unsigned short ** __ctype_b_loc();
extern const unsigned short ** __ctype_b_loc();
extern const unsigned short ** __ctype_b_loc();
extern const unsigned short ** __ctype_b_loc();
extern const unsigned short ** __ctype_b_loc();
extern const unsigned short ** __ctype_b_loc();
extern const unsigned short ** __ctype_b_loc();
extern const unsigned short ** __ctype_b_loc();
extern const unsigned short ** __ctype_b_loc();
extern int tolower(int);

extern int match_class (int c, int cl) {
  int res;
  switch (tolower(cl)) {
    case 'a' : res = ((*__ctype_b_loc ())[(int) ((c))] & (unsigned short int) _ISalpha); break;
    case 'c' : res = ((*__ctype_b_loc ())[(int) ((c))] & (unsigned short int) _IScntrl); break;
    case 'd' : res = ((*__ctype_b_loc ())[(int) ((c))] & (unsigned short int) _ISdigit); break;
    case 'g' : res = ((*__ctype_b_loc ())[(int) ((c))] & (unsigned short int) _ISgraph); break;
    case 'l' : res = ((*__ctype_b_loc ())[(int) ((c))] & (unsigned short int) _ISlower); break;
    case 'p' : res = ((*__ctype_b_loc ())[(int) ((c))] & (unsigned short int) _ISpunct); break;
    case 's' : res = ((*__ctype_b_loc ())[(int) ((c))] & (unsigned short int) _ISspace); break;
    case 'u' : res = ((*__ctype_b_loc ())[(int) ((c))] & (unsigned short int) _ISupper); break;
    case 'w' : res = ((*__ctype_b_loc ())[(int) ((c))] & (unsigned short int) _ISalnum); break;
    case 'x' : res = ((*__ctype_b_loc ())[(int) ((c))] & (unsigned short int) _ISxdigit); break;
    case 'z' : res = (c == 0); break;
    default: return (cl == c);
  }
  return (((*__ctype_b_loc ())[(int) ((cl))] & (unsigned short int) _ISlower) ? res : !res);
}

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



extern void luaC_barrierback_(lua_State *, GCObject *);
extern Node * mainposition(const Table *, int, const Value *);
extern TValue * luaH_set(lua_State *, Table *, const TValue *);
extern void rehash(lua_State *, Table *, const TValue *);
extern Node * getfreepos(Table *);
extern Node * mainpositionTV(const Table *, const TValue *);
extern void luaG_runerror(lua_State *, const char *, ...);
extern long __builtin_expect(long, long);
extern int luaV_flttointeger(lua_Number, lua_Integer *, F2Imod);
extern void luaG_runerror(lua_State *, const char *, ...);
extern long __builtin_expect(long, long);

TValue *luaH_newkey (lua_State *L, Table *t, const TValue *key) {
  Node *mp;
  TValue aux;
  if ((__builtin_expect((((((((((key))->tt_)) & 0x0F)) == (0))) != 0), 0)))
    luaG_runerror(L, "table index is nil");
  else if (((((key))->tt_) == (((3) | ((1) << 4))))) {
    lua_Number f = (((key)->value_).n);
    lua_Integer k;
    if (luaV_flttointeger(f, &k, F2Ieq)) {
      { TValue *io=(&aux); ((io)->value_).i=(k); ((io)->tt_=(((3) | ((0) << 4)))); };
      key = &aux;
    }
    else if ((__builtin_expect((((!(((f))==((f))))) != 0), 0)))
      luaG_runerror(L, "table index is NaN");
  }
  mp = mainpositionTV(t, key);
  if (!((((((((&(mp)->i_val)))->tt_)) & 0x0F)) == (0)) || ((t)->lastfree == ((void*)0))) {
    Node *othern;
    Node *f = getfreepos(t);
    if (f == ((void*)0)) {
      rehash(L, t, key);

      return luaH_set(L, t, key);
    }
    ((void)0);
    othern = mainposition(t, ((mp)->u.key_tt), &((mp)->u.key_val));
    if (othern != mp) {

      while (othern + ((othern)->u.next) != mp)
        othern += ((othern)->u.next);
      ((othern)->u.next) = ((int)((f - othern)));
      *f = *mp;
      if (((mp)->u.next) != 0) {
        ((f)->u.next) += ((int)((mp - f)));
        ((mp)->u.next) = 0;
      }
      (((&(mp)->i_val))->tt_=(((0) | ((1) << 4))));
    }
    else {

      if (((mp)->u.next) != 0)
        ((f)->u.next) = ((int)(((mp + ((mp)->u.next)) - f)));
      else ((void)0);
      ((mp)->u.next) = ((int)((f - mp)));
      mp = f;
    }
  }
  { Node *n_=(mp); const TValue *io_=(key); n_->u.key_val = io_->value_; n_->u.key_tt = io_->tt_; ((void)L, ((void)0)); };
  ( ((((key)->tt_) & (1 << 6)) && ((((&(((union GCUnion *)((t)))->gc)))->marked) & ((1<<(5)))) && ((((((key)->value_).gc))->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrierback_(L,(&(((union GCUnion *)((t)))->gc))) : ((void)((0))));
  ((void)0);
  return (&(mp)->i_val);
}
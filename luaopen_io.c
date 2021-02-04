
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

typedef luaL_Stream LStream;

extern int io_write(lua_State *);
extern int io_type(lua_State *);
extern int io_tmpfile(lua_State *);
extern int io_read(lua_State *);
extern int io_popen(lua_State *);
extern int io_output(lua_State *);
extern int io_open(lua_State *);
extern int io_lines(lua_State *);
extern int io_input(lua_State *);
extern int io_flush(lua_State *);
extern int io_close(lua_State *);

static const luaL_Reg iolib[] = {
  {"close", io_close},
  {"flush", io_flush},
  {"input", io_input},
  {"lines", io_lines},
  {"open", io_open},
  {"output", io_output},
  {"popen", io_popen},
  {"read", io_read},
  {"tmpfile", io_tmpfile},
  {"type", io_type},
  {"write", io_write},
  {((void*)0), ((void*)0)}
};

extern void createstdfile(lua_State *, FILE *, const char *, const char *);
extern void createstdfile(lua_State *, FILE *, const char *, const char *);
extern void createstdfile(lua_State *, FILE *, const char *, const char *);
extern void createmeta(lua_State *);
extern void luaL_setfuncs(lua_State *, const luaL_Reg *, int);
extern void lua_createtable(lua_State *, int, int);
extern void luaL_checkversion_(lua_State *, lua_Number, size_t);

extern int luaopen_io (lua_State *L) {
  (luaL_checkversion_(L, 504, (sizeof(lua_Integer)*16 + sizeof(lua_Number))), lua_createtable(L, 0, sizeof(iolib)/sizeof((iolib)[0]) - 1), luaL_setfuncs(L,iolib,0));
  createmeta(L);

  createstdfile(L, stdin, ("_IO_" "input"), "stdin");
  createstdfile(L, stdout, ("_IO_" "output"), "stdout");
  createstdfile(L, stderr, ((void*)0), "stderr");
  return 1;
}
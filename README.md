# lua-func

The Lua interpreter split in a way such that each function is in it's own file. Most functions can
just be moved to a new file with few problems, except for a few files that were very hard to split
up, for example the `lundump.c` file.

In its current state the project does not aquire any additional CHERI security guarantees.
However, this will allow for experimenting with different groupings of functions by linking the
different object files together in different ways. The main purpose of doing this is to get
additional security under CHERI without any CHERI specific code. This can be done by exploiting
the runtime linker of CheriBSD.

Some of the Lua tests do not pass, and they are commented out: one of the popen tests in 
files.lua:747, and the entire main.lua file. This amounts to roughly 15% of the tests failing.

Build script:

```sh

#/bin/sh

set -e

CC=${CC:-clang}

for source_file in *.c; do
	echo "lib${source_file%.c}.so"
	${CC} ${source_file} -fPIC -Wno-parentheses-equality -shared -glldb -lm -o lib${source_file%.c}.so
done

set libs=""
for lib in *.so; do
	libs=$libs$(echo $lib | sed -E 's/lib(.*)\.so/ -l\1/gm')
done
echo $libs
exit 0

echo clang main.o -lm -glldb $libs -o lua.shared
clang main.o -lm -glldb -L. $libs -Wl,-rpath,. -o lua.shared

```

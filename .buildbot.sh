#/bin/sh

set -e

CC=${CC:-clang}

for source_file in *.c; do
	echo "lib${source_file%.c}.so"
	${CC} ${source_file} -fPIC -Wno-parentheses-equality -shared -glldb -lm -o lib${source_file%.c}.so &
done
wait

set libs=""
for lib in *.so; do
	libs=$libs$(echo $lib | sed -E 's/lib(.*)\.so/ -l\1/gm')
done

clang -c main.c
clang main.o -lm -glldb -L. $libs -Wl,-rpath,. -o lua.shared


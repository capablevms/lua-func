#/bin/sh

set -e

CC=${CC:-~/cheri/output/sdk/bin/clang}
CFLAGS=${CFLAGS:--fuse-ld=lld --config cheribsd-riscv64-purecap.cfg}

for source_file in *.c; do
	echo "lib${source_file%.c}.so"
	${CC} ${CFLAGS} ${source_file} -fPIC -Wno-parentheses-equality -shared -glldb -lm -o lib${source_file%.c}.so &
done
wait

set libs=""
for lib in *.so; do
	libs=$libs$(echo $lib | sed -E 's/lib(.*)\.so/ -l\1/gm')
done

${CC} ${CFLAGS} -fPIE -c main.c
${CC} ${CFLAGS} main.o -lm -glldb -fPIC -L. $libs -Wl,-rpath,/root/lua -o lua.shared


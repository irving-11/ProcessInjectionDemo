#!/bin/sh
gcc -g -c "$1" -o ./test.o
echo "--- add BTF section ---"
pahole -JV ./test.o > /dev/null
echo "-------- DONE! --------"
strip ./test.o
echo "----- extract BTF -----"
gcc readBTF.c -o ./readBTF
./readBTF ./test.o ./tmp > /dev/null
echo "-------- DONE! --------"
echo "-------- PRINT --------"
./btfparse/build/tools/dump-btf/dump-btf ./tmp
echo "-------- DONE! --------"

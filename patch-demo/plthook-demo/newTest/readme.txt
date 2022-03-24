


generate libplthook.so
gcc ../plthook_elf.c -fPIC -shared -o libplthook.so

generate libtesta.so:
gcc testa.c -fPIC -shared -o libtesta.so

generate demo1:
gcc -Werror -Wall -g -pipe -O2 -Wno-unused-variable -Wno-unused-function -o demo1 demo1.cpp -L/home/ubuntu/Documents/plthook/newTest -lplthook -ltesta -ldl

run demo1:
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/ubuntu/Documents/plthook/newTest/
export LD_LIBRARY_PATH
./demo1

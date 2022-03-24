CXXFLAGS = -Werror -Wall -g -pipe -O2 -Wno-unused-variable -Wno-unused-function
CFLAGS = -Werror -Wall -g -pipe -O2 -Wno-unused-variable -Wno-unused-function

INCLUDE = -I. -I./plthook
LIBPATH = -L.
LIBS = -ltesta -ltesta_hook -lplthook -ldl 

OPTIONS = -Wl,-rpath,./

TARGET1 = demo1
TARGET1_OBJS = demo1.o

TARGET2 = demo2
TARGET2_OBJS = demo2.o


.PHONY: clean plthook

TARGET_LIST = $(TARGET1) $(TARGET2)

all: testa testa_hook plthook $(TARGET_LIST)

testa:
	$(CXX) $(CFLAGS) testa.c -fPIC -shared -o libtesta.so

testa_hook:
	$(CXX) $(CFLAGS) testa_hook.c -fPIC -shared -o libtesta_hook.so

plthook:
	$(CC) $(CFLAGS) ../plthook_elf.c -fPIC -shared -o libplthook.so

$(TARGET1): $(TARGET1_OBJS)
	$(CXX) -o $@ $^ $(INCLUDE) $(LIBPATH) $(LIBS) $(OPTIONS)
	@echo "build $(TARGET1) ok"

$(TARGET2): $(TARGET2_OBJS)
	$(CXX) -o $@ $^ $(INCLUDE) $(LIBPATH) $(LIBS) $(OPTIONS)
	@echo "build $(TARGET2) ok"

clean:
	rm -f *.o *.so $(TARGET_LIST)

%.o: %.cpp
	$(CC) $(CXXFLAGS) $(INCLUDE) -c $<
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

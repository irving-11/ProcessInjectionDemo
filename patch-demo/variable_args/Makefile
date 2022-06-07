
TARGET = test1 patch_poc

CFLAGS = -O0 -g

all: $(TARGET)

$(TARGET): %: %.c
	gcc $(CFLAGS) $^ -o  $@
	objdump -S $@ > $@.asm

clean:
	rm $(TARGET) *.asm

.PHONY: clean
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void write_memory(int address, char value) {
	*((char*) address) = value;
}

void kernel_main() {
	int i;
	for (i = 0xa0000; i < 0xa0a00; i++) {
		write_memory(i, i & 0xff);
	}
}

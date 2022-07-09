#include "arch.h"

#ifdef X64
#define NAME "X64"
#else
#define NAME "X86"
#endif

// TODO redefine

int main() {
	printf(NAME); // 14
}
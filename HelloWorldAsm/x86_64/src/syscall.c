#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>



int
_start(int argc, char *argv[])
{
	__asm__(
			"mov rax, 60; exit("
			"mov rdi, 0;   EXIT_SUCCESS"
			"syscall; );
	);
}
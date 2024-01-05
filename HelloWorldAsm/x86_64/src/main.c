#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>

int	main(void)
{
	/* write(STDOUT_FILENO,"Hey!\n", 5); */
	char *str;

	str = "Wello Horld!\n";
//	write(STDOUT_FILENO, str, strlen(str));
	syscall(SYS_write, STDOUT_FILENO, str, strlen(str));
	return (0);
}
